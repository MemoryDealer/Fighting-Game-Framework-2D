// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: LobbyState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements LobbyState class.
// ================================================ //

#include "LobbyState.hpp"
#include "Engine.hpp"
#include "GUILobbyState.hpp"
#include "StageManager.hpp"
#include "PlayerManager.hpp"
#include "Input.hpp"
#include "GameManager.hpp"
#include "Config.hpp"
#include "App.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NetMessage.hpp"
#include "Widget.hpp"
#include "WidgetListbox.hpp"
#include "Label.hpp"

// ================================================ //

LobbyState::LobbyState(void) :
m_pGUI(nullptr),
m_pBackground(nullptr)
{
	Config c("ExtMF.cfg");
	m_pGUI.reset(new GUILobbyState(c.parseValue("GUI", "lobbystate")));
}

// ================================================ //

LobbyState::~LobbyState(void)
{

}

// ================================================ //

void LobbyState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering LobbyState...");

	m_pBackground.reset(new Stage("Data/Stages/lobby.stage"));

	if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
		m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
			"Server initialized.");
	}
	else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
		m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
			"Attempting server connection...");
		Client::getSingletonPtr()->connect();
	}

	// Add username to player list.
	m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->addString(
		GameManager::getSingletonPtr()->getUsername());

	GameManager::getSingletonPtr()->setState(GameManager::NIL);
}

// ================================================ //

void LobbyState::exit(void)
{
	// Notify server of disconnection if we are a client.
	if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
		Client::getSingletonPtr()->disconnect();
	}

	m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->clear();
	m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->clear();

	Log::getSingletonPtr()->logMessage("Exiting LobbyState...");
}

// ================================================ //

bool LobbyState::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing LobbyState...");

	return true;
}

// ================================================ //

void LobbyState::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming LobbyState...");
}

// ================================================ //

void LobbyState::handleInput(SDL_Event& e)
{
	// Acquire a pointer to the player under the control of the current gamepad here (avoids copied & pasted code below).
	Player* player = nullptr;
	if (e.type == SDL_CONTROLLERBUTTONDOWN ||
		e.type == SDL_CONTROLLERBUTTONUP ||
		e.type == SDL_CONTROLLERAXISMOTION){
		player = (e.cdevice.which == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getRedPlayer() : (e.cdevice.which == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getBluePlayer() : nullptr;

		if (player == nullptr){
			Log::getSingletonPtr()->logMessage("WARNING: Unregistered gamepad sending input (ID: " + Engine::toString(e.cdevice.which) + ")");
			return;
		}
	}

	if (e.type == SDL_KEYDOWN){

		// Process hard-coded keys.
		switch (e.key.keysym.sym){
		default:
			break;

		case SDLK_ESCAPE:
			if (m_pGUI->isEditingText()){
				m_pGUI->setEditingText(Widget::NONE);
			}
			else{
				if (m_pGUI->getCurrentLayer() == GUILobbyState::Layer::ROOT){
					m_quit = true;
				}
				else{
					m_pGUI->popLayer();
				}
			}
			break;

		case SDLK_RETURN:
			if (m_pGUI->isEditingText()){
				// Build message text with user name preceding the message itself.
				std::string message = GameManager::getSingletonPtr()->getUsername() +
					": " + m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->getText();
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
					/*std::shared_ptr<Packet> data(new Packet(Packet::CHAT));
					data->setMessage(message);
					Server::getSingletonPtr()->broadcastToAllClients(data.get());*/
				}
				else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->chat(message);
				}
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(message);
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->setLabel("");
			}
			break;

		case SDLK_BACKSPACE:
			if (m_pGUI->isEditingText()){
				m_pGUI->handleTextInput("", true);
			}
			break;

		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_LEFT:
		case SDLK_RIGHT:
			// Automatically switch to navigation mode when arrows are pressed.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
			}

			if (!m_pGUI->getSelectorPressed()){
				// Prevent user from navigating away while pressing a button.
				int widget = m_pGUI->getSelectedWidget();
				if (widget == Widget::NONE){
					m_pGUI->setSelectedWidget(0);
				}
				else{
					// Navigate the selector to the linked Widget.
					Widget* pWidget = m_pGUI->getWidgetPtr(widget);
					switch (e.key.keysym.sym){
					default:
					case SDLK_UP:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
						break;

					case SDLK_DOWN:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
						break;

					case SDLK_LEFT:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
						break;

					case SDLK_RIGHT:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
						break;
					}
				}
			}
			break;

		case SDLK_r:
			{
				// Reload GUI and background.
				//Config c("ExtMF.cfg");
				//m_pGUI.reset(new GUILobbyState(c.parseValue("GUI", "lobbystate")));
				m_pBackground.reset(new Stage("Data/Stages/lobby.stage"));
			}
			break;

		case SDLK_i:
			if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
				Server::getSingletonPtr()->dbgPrintAllConnectedClients();
			}
			break;

		case SDLK_o:
			if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
				Server::getSingletonPtr()->dbgPrintReadyQueue();
			}
			break;

		case SDLK_j:
			m_pGUI->setMessageBoxText("Hello there, this is a test message from Satan.");
			m_pGUI->showMessageBox(true);
			break;

		case SDLK_k:
			m_pGUI->showMessageBox(false);
			break;
		}
	}

	if (e.type == SDL_CONTROLLERBUTTONDOWN){

		if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
			m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
		}

		if (!m_pGUI->getSelectorPressed()){
			// Prevent user from navigating away while pressing a button.
			int widget = m_pGUI->getSelectedWidget();
			if (widget == Widget::NONE){
				m_pGUI->setSelectedWidget(0);
			}
			else{
				// Navigate to the linked Widget.
				Widget* pWidget = m_pGUI->getWidgetPtr(widget);
				switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
				default:
					break;

				case Input::BUTTON_UP:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
					break;

				case Input::BUTTON_DOWN:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
					break;

				case Input::BUTTON_LEFT:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
					break;

				case Input::BUTTON_RIGHT:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
					break;

				case Input::BUTTON_BACK:
					m_pGUI->popLayer();
					break;
				}
			}
		}
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION){

		if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
			m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
		}

		if (!m_pGUI->getSelectorPressed()){
			// Prevent user from navigating away while pressing a button.
			int widget = m_pGUI->getSelectedWidget();
			if (widget == Widget::NONE){
				m_pGUI->setSelectedWidget(0);
			}
			else{
				// These booleans prevent the selector from skipping Widgets in 
				// between two end Widgets when a joystick is held down.
				static bool xAxisReset = true;
				static bool yAxisReset = true;

				Widget* pWidget = m_pGUI->getWidgetPtr(widget);
				const int deadzone = player->getInput()->getPadDeadzone();

				// Process Y-axis movement.
				Sint16 value = SDL_GameControllerGetAxis(player->getInput()->getPad(), static_cast<SDL_GameControllerAxis>(1));
				if (value < -deadzone && yAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
					yAxisReset = false;
				}
				else if (value > deadzone && yAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
					yAxisReset = false;
				}
				else if (value < deadzone && value > -deadzone){
					yAxisReset = true;
				}

				// Process X-axis movement.
				value = SDL_GameControllerGetAxis(player->getInput()->getPad(), static_cast<SDL_GameControllerAxis>(0));
				if (value < -deadzone && xAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
				}
				else if (value > deadzone && xAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
				}
				else if (value < deadzone && value > -deadzone){
					xAxisReset = true;
				}
			}
		}
	}
}

// ================================================ //

void LobbyState::processGUIAction(const int type)
{
	static int lastSelectedWidget = Widget::NONE;
	m_pGUI->setEditingText(Widget::NONE);

	switch (type){
	default:
		return;

	case GUI::Action::BEGIN_PRESS:
		if (m_pGUI->getSelectedWidget() != Widget::NONE){
			lastSelectedWidget = m_pGUI->getSelectedWidget();
			m_pGUI->getWidgetPtr(lastSelectedWidget)->setAppearance(Widget::Appearance::PRESSED);
		}
		break; // End BEGIN_PRESS.

	case GUI::Action::FINISH_PRESS:
		// When a button is pressed in selector mode, reset it back to select appearance.
		if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
			m_pGUI->getSelectedWidgetPtr()->setAppearance(Widget::Appearance::SELECTED);
		}

		// Don't let this button be pressed unless BEGIN_PRESS started on it.
		if (m_pGUI->getSelectedWidget() != lastSelectedWidget){
			if (lastSelectedWidget < m_pGUI->getCurrentLayerPtr()->getNumWidgets()){
				m_pGUI->getWidgetPtr(lastSelectedWidget)->setAppearance(Widget::Appearance::IDLE);
				return;
			}
		}

		// Find the current layer, then test that layer's widgets for actions.
		switch (m_pGUI->getCurrentLayerPtr()->getID()){
		default:
			break;

		case GUI::MESSAGEBOX:
			if (m_pGUI->getSelectedWidget() == GUILayerMessageBox::BUTTON_OK)
				m_pGUI->showMessageBox(false);
			break;

		case GUILobbyState::Layer::ROOT:
			switch (m_pGUI->getSelectedWidget()){
			default:
				break;

			case GUILobbyStateLayer::Root::BUTTON_READY:
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
					Server::getSingletonPtr()->ready(0);
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
						"You are ready!");
				}
				else if(GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->ready(0);
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
						"You are ready!");
				}
				break;

			case GUILobbyStateLayer::Root::BUTTON_START:
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
					// Load fighters being used by players.
					if (Server::getSingletonPtr()->getReadyQueueSize() < 2){
						m_pGUI->setMessageBoxText("Not enough players are ready!");
						m_pGUI->showMessageBox(true);
						break;
					}
					ReadyClient red = Server::getSingletonPtr()->getNextRedPlayer();
					ReadyClient blue = Server::getSingletonPtr()->getNextBluePlayer();
					if (PlayerManager::getSingletonPtr()->load(red.fighter, blue.fighter)){
						// Assign each player's mode, checking for local or net play.
						if (red.username.compare(GameManager::getSingletonPtr()->getUsername()) == 0){
							PlayerManager::getSingletonPtr()->getRedPlayer()->setMode(Player::Mode::LOCAL);
							GameManager::getSingletonPtr()->setState(GameManager::PLAYING_RED);
						}
						else{
							PlayerManager::getSingletonPtr()->getRedPlayer()->setMode(Player::Mode::NET);
						}
						if (blue.username.compare(GameManager::getSingletonPtr()->getUsername()) == 0){
							PlayerManager::getSingletonPtr()->getBluePlayer()->setMode(Player::Mode::LOCAL);
							GameManager::getSingletonPtr()->setState(GameManager::PLAYING_BLUE);
						}
						else{
							PlayerManager::getSingletonPtr()->getBluePlayer()->setMode(Player::Mode::NET);
						}

						Server::getSingletonPtr()->startGame();
						this->pushAppState(this->findByName(GAME_STATE));
					}
					else{
						Log::getSingletonPtr()->logMessage("Failed to load fighters!");
					}
				}
				break;

			case GUILobbyStateLayer::Root::TEXTBOX_SEND:
				m_pGUI->setEditingText(GUILobbyStateLayer::Root::TEXTBOX_SEND);
				break;

			case GUILobbyStateLayer::Root::BUTTON_SEND:
			{
				std::string message = GameManager::getSingletonPtr()->getUsername() +
					": " + m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->getText();
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
					Server::getSingletonPtr()->chat(message);
				}
				else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->chat(message);
				}
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(message);
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->setLabel("");
			}
				break;

			case GUILobbyStateLayer::Root::BUTTON_EXIT:
				m_quit = true;
				break;
			}
			break;
		}
		break; // End FINISH_PRESS.
	}
}

// ================================================ //

void LobbyState::update(double dt)
{
	if (m_quit == true){
		this->popAppState();
		return;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_quit = true;
			break;

		case SDL_KEYDOWN:
			// Send a BEGIN_PRESS action to processGUI() if the selection 
			// button is held.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (!m_pGUI->isEditingText() && e.key.keysym.sym == SDLK_SPACE){
					m_pGUI->setSelectorPressed(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_KEYUP:
			// Send a FINISH_PRESS action to processGUI() if the selection 
			// button is released.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (!m_pGUI->isEditingText() && e.key.keysym.sym == SDLK_SPACE){
					m_pGUI->setSelectorPressed(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
				// If this is a networked game, we should update even if the window is not 
				// in focus.
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER ||
					GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					break;
				}
				else{
					Engine::getSingletonPtr()->setWindowFocused(false);
				}
			}
			break;

		case SDL_MOUSEMOTION:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				m_pGUI->setNavigationMode(GUI::NavMode::MOUSE);
				m_pGUI->clearSelector();
			}
			m_pGUI->setMousePos(e.motion.x, e.motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				if (e.button.button == SDL_BUTTON_LEFT){
					m_pGUI->setLeftMouseDown(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
				else if (e.button.button == SDL_BUTTON_RIGHT){
					m_pGUI->setRightMouseDown(true);
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				if (e.button.button == SDL_BUTTON_LEFT){
					m_pGUI->setLeftMouseDown(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
				else{
					m_pGUI->setRightMouseDown(false);
				}
			}
			break;

		case SDL_TEXTINPUT:
			m_pGUI->handleTextInput(e.text.text);
			break;

		case SDL_TEXTEDITING:
			m_pGUI->handleTextInput(e.edit.text);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pBackground->update(dt);
	m_pGUI->update(dt);
	if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
		for (Server::getSingletonPtr()->m_packet = Server::getSingletonPtr()->m_peer->Receive();
			Server::getSingletonPtr()->m_packet;
			Server::getSingletonPtr()->m_peer->DeallocatePacket(Server::getSingletonPtr()->m_packet),
			Server::getSingletonPtr()->m_packet = Server::getSingletonPtr()->m_peer->Receive()){
			switch (Server::getSingletonPtr()->m_packet->data[0]){
			default:
				break;

			case ID_DISCONNECTION_NOTIFICATION:
				if (Server::getSingletonPtr()->isClientConnected(Server::getSingletonPtr()->m_packet->systemAddress)){
					std::string username = Server::getSingletonPtr()->m_clients[Server::getSingletonPtr()->getClient(
						Server::getSingletonPtr()->m_packet->systemAddress)].username;
					Log::getSingletonPtr()->logMessage("SERVER: Removing client [" +
						std::string(Server::getSingletonPtr()->m_packet->systemAddress.ToString()) + "]");
					Server::getSingletonPtr()->removeFromReadyQueue(username);
					Server::getSingletonPtr()->removeClient(Server::getSingletonPtr()->m_packet->systemAddress);

					// Tell all other clients.
					{
						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
						bit.Write(username.c_str());
						Server::getSingletonPtr()->broadcast(bit, HIGH_PRIORITY, RELIABLE);
					}

					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
						std::string(Server::getSingletonPtr()->getLastPacketStrData()) + " disconnected!");
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->removeEntry(
						std::string(Server::getSingletonPtr()->getLastPacketStrData()));
				}
				break;

			case ID_CONNECTION_LOST:
				{
					std::string username = Server::getSingletonPtr()->m_clients[Server::getSingletonPtr()->getClient(
						Server::getSingletonPtr()->m_packet->systemAddress)].username;
					Log::getSingletonPtr()->logMessage("SERVER: Removing client [" +
						std::string(Server::getSingletonPtr()->m_packet->systemAddress.ToString()) + "]");
					Server::getSingletonPtr()->removeFromReadyQueue(username);
					Server::getSingletonPtr()->removeClient(Server::getSingletonPtr()->m_packet->systemAddress);
					RakNet::BitStream bit;
					bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_LOST_CONNECTION));
					bit.Write(username.c_str());
					Server::getSingletonPtr()->broadcast(bit, HIGH_PRIORITY, RELIABLE);

					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
						username + " lost connection!");
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->removeEntry(
						username);
				}
				break;

			case NetMessage::SET_USERNAME:
			{
				RakNet::BitStream bit(Server::getSingletonPtr()->m_packet->data, 
					Server::getSingletonPtr()->m_packet->length, false);
				RakNet::RakString rs;
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				bit.Read(rs);

				if (Server::getSingletonPtr()->isUsernameInUse(rs.C_String())){
					RakNet::BitStream reject;
					reject.Write(static_cast<RakNet::MessageID>(NetMessage::USERNAME_IN_USE));

					Server::getSingletonPtr()->send(reject, Server::getSingletonPtr()->m_packet->systemAddress, HIGH_PRIORITY, RELIABLE);
				}
				else{
					Log::getSingletonPtr()->logMessage("SERVER: Client [" + std::string(
						Server::getSingletonPtr()->m_packet->systemAddress.ToString()) +
						"] connected with username \"" + rs.C_String() + "\"");

					// Send a list of players to newly connected client.
					Server::getSingletonPtr()->sendPlayerList(Server::getSingletonPtr()->m_packet->systemAddress);

					// Add them to the client list.
					Server::getSingletonPtr()->registerClient(rs.C_String(), Server::getSingletonPtr()->m_packet->systemAddress);

					Server::getSingletonPtr()->broadcast(Server::getSingletonPtr()->m_packet, HIGH_PRIORITY, RELIABLE, 
						Server::getSingletonPtr()->m_packet->systemAddress);

					std::string username = Server::getSingletonPtr()->getLastPacketStrData();
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
						username + std::string(" connected!"));
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->addString(
						username);
				}
			}
				break;

			case NetMessage::CHAT:
				Server::getSingletonPtr()->broadcast(Server::getSingletonPtr()->m_packet, 
					HIGH_PRIORITY, RELIABLE_ORDERED, Server::getSingletonPtr()->m_packet->systemAddress);
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					Server::getSingletonPtr()->getLastPacketStrData());
				break;

			case NetMessage::READY:
				// Add username to ready queue and broadcast.
				if (Server::getSingletonPtr()->isClientConnected(Server::getSingletonPtr()->m_packet->systemAddress)){
					int client = Server::getSingletonPtr()->getClient(Server::getSingletonPtr()->m_packet->systemAddress);
					RakNet::BitStream data(Server::getSingletonPtr()->m_packet->data, Server::getSingletonPtr()->m_packet->length, false);
					data.IgnoreBytes(sizeof(RakNet::MessageID));
					Uint32 fighter;
					data.Read(fighter);
					if (Server::getSingletonPtr()->addToReadyQueue(Server::getSingletonPtr()->m_clients[client].username, fighter)){
						std::string username = Server::getSingletonPtr()->m_clients[client].username;

						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::READY));
						bit.Write(username.c_str());
						bit.Write(fighter);

						Server::getSingletonPtr()->broadcast(bit, HIGH_PRIORITY, RELIABLE_ORDERED, 
							Server::getSingletonPtr()->m_packet->systemAddress);
						
						m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
							std::string(Server::getSingletonPtr()->getLastPacketStrData()) + " is ready!");
					}
				}
				break;
			}
		}
	}
	else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
		for (Client::getSingletonPtr()->m_packet = Client::getSingletonPtr()->m_peer->Receive();
			Client::getSingletonPtr()->m_packet;
			Client::getSingletonPtr()->m_peer->DeallocatePacket(Client::getSingletonPtr()->m_packet),
			Client::getSingletonPtr()->m_packet = Client::getSingletonPtr()->m_peer->Receive()){
			switch (Client::getSingletonPtr()->m_packet->data[0]){
			default:
				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString("Connected to server!");
				{
					// Store the server system address for future use.
					Client::getSingletonPtr()->m_serverAddr = Client::getSingletonPtr()->m_packet->systemAddress;

					// Send the server the username.
					RakNet::BitStream bit;
					bit.Write(static_cast<RakNet::MessageID>(NetMessage::SET_USERNAME));
					Log::getSingletonPtr()->logMessage("Sending username \"" +
						GameManager::getSingletonPtr()->getUsername() + "\" to server.");
					bit.Write(GameManager::getSingletonPtr()->getUsername().c_str());
					Client::getSingletonPtr()->send(bit, HIGH_PRIORITY, RELIABLE);
				}
				break;

			case ID_CONNECTION_LOST:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString("Lost connection to server.");
				break;

			case NetMessage::SET_USERNAME:
			{
				std::string username = Client::getSingletonPtr()->getLastPacketStrData();
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					username + std::string(" connected!"));
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->addString(
					username);
			}
				break;

			case NetMessage::USERNAME_IN_USE:
				Client::getSingletonPtr()->disconnect();
				GameManager::getSingletonPtr()->setState(NetMessage::USERNAME_IN_USE);
				m_quit = true;
				break;

			case NetMessage::CLIENT_DISCONNECTED:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					std::string(Client::getSingletonPtr()->getLastPacketStrData()) + " disconnected!");
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->removeEntry(
					std::string(Client::getSingletonPtr()->getLastPacketStrData()));
				break;

			case NetMessage::CLIENT_LOST_CONNECTION:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					std::string(Client::getSingletonPtr()->getLastPacketStrData()) + " lost connection!");
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->removeEntry(
					std::string(Client::getSingletonPtr()->getLastPacketStrData()));
				break;

			case NetMessage::PLAYER_LIST:
			{
				// Extract each player username and add to list.										
				RakNet::BitStream bit(Client::getSingletonPtr()->getLastPacket()->data,
					Client::getSingletonPtr()->getLastPacket()->length, false);
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				Uint32 numPlayers = 0;
				bit.Read(static_cast<Uint32&>(numPlayers));
				for (Uint32 i = 0; i < numPlayers; ++i){
					char player[GameManager::MAX_USERNAME_LENGTH + 1];
					bit.Read(player);
					m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_PLAYERS)->addString(player);
				}
			}
				break;

			case NetMessage::CHAT:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					Client::getSingletonPtr()->getLastPacketStrData());
				break;

			case NetMessage::READY:
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT)->addString(
					std::string(Client::getSingletonPtr()->getLastPacketStrData()) + " is ready!");
				// Show fighter...
				break;

			case NetMessage::PLAYING_RED:
				GameManager::getSingletonPtr()->setState(GameManager::PLAYING_RED);
				break;

			case NetMessage::PLAYING_BLUE:
				GameManager::getSingletonPtr()->setState(GameManager::PLAYING_BLUE);
				break;

			case NetMessage::SERVER_STARTING_GAME:
				GameManager::getSingletonPtr()->setState(GameManager::SPECTATING);
				// Load the fighters being used this match.
				{
					RakNet::BitStream bit(Client::getSingletonPtr()->m_packet->data,
						Client::getSingletonPtr()->m_packet->length, false);
					bit.IgnoreBytes(sizeof(RakNet::MessageID));
					Uint32 red = 0, blue = 0;
					bit.Read(red);
					bit.Read(blue);
					PlayerManager::getSingletonPtr()->load(red, blue);
				}
				this->pushAppState(this->findByName(GAME_STATE));
				break;
			}
		}
	}

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //