// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GameState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GameState class.
// ================================================ //

#include "GameState.hpp"
#include "Engine.hpp"
#include "ObjectManager.hpp"
#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "Stage.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "GUIGameState.hpp"
#include "Widget.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NetMessage.hpp"
#include "GamepadManager.hpp"
#include "Game.hpp"
#include "Timer.hpp"

// ================================================ //

GameState::GameState(void) :
m_pObjectManager(new ObjectManager()),
m_pGUI(nullptr),
m_pServerUpdateTimer(new Timer()),
m_pResetServerInputTimer(new Timer())
{
	Config c(Engine::getSingletonPtr()->getSettingsFile());
	m_pGUI.reset(new GUIGameState(Engine::getSingletonPtr()->getDataDirectory() + 
		"/" + c.parseValue("GUI", "gamestate")));
}

// ================================================ //

GameState::~GameState(void)
{

}

// ================================================ //

void GameState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering GameState...");

	if (Game::getSingletonPtr()->getMode() == Game::SERVER){
		m_pServerUpdateTimer->restart();
		m_pResetServerInputTimer->restart();
	}

	PlayerManager::getSingletonPtr()->getRedPlayer()->setHealthBarPtr(m_pGUI->getWidgetPtr(GUIGameStateLayer::Root::HEALTHBAR_RED));
	PlayerManager::getSingletonPtr()->getBluePlayer()->setHealthBarPtr(m_pGUI->getWidgetPtr(GUIGameStateLayer::Root::HEALTHBAR_BLUE));

	// Show correct fighter names.
	m_pGUI->getWidgetPtr(GUIGameStateLayer::Root::STATIC_RED_FIGHTER)->setLabel(
		PlayerManager::getSingletonPtr()->getRedFighterName());
	m_pGUI->getWidgetPtr(GUIGameStateLayer::Root::STATIC_BLUE_FIGHTER)->setLabel(
		PlayerManager::getSingletonPtr()->getBlueFighterName());

	Game::getSingletonPtr()->setError(0);
}

// ================================================ //

void GameState::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting GameState...");
}

// ================================================ //

bool GameState::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing GameState...");

	return true;
}

// ================================================ //

void GameState::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming GameState...");
}

// ================================================ //

void GameState::handleInputDt(SDL_Event& e, double dt)
{
	// Acquire a pointer to the player under the control of the current gamepad 
	// here (avoids copied & pasted code below).
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
		///printf("KEYDOWN: %d\n", e.key.keysym.sym);

		// Process mapped buttons.
		// Red Player.
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED ||
			(Game::getSingletonPtr()->getMode() == Game::LOCAL && 
			PlayerManager::getSingletonPtr()->getRedPlayer()->getMode() == Player::Mode::LOCAL)){
			int key = PlayerManager::getSingletonPtr()->getRedPlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym);
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getButton(key) == false){
				switch (key){
				default:
					break;

				case Input::BUTTON_LEFT:
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
					}
					break;

				case Input::BUTTON_RIGHT:
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
					}
					break;

				case Input::BUTTON_UP:
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_UP, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_UP, true, dt);
					}
					break;

				case Input::BUTTON_DOWN:
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_DOWN, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_DOWN, true, dt);
					}
					break;

				case Input::BUTTON_LP:
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LP, true);					
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_LP, true, dt);
					}
					break;
				}
			}
		}
		// Blue Player.
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE ||
				 (Game::getSingletonPtr()->getMode() == Game::LOCAL && 
				 PlayerManager::getSingletonPtr()->getBluePlayer()->getMode() == Player::Mode::LOCAL)){
			int key = PlayerManager::getSingletonPtr()->getBluePlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym);
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getButton(key) == false){
				switch (key){
				default:
					break;

				case Input::BUTTON_LEFT:
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
					}
					break;

				case Input::BUTTON_RIGHT:
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
					}
					break;

				case Input::BUTTON_UP:
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_UP, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_UP, true, dt);
					}
					break;

				case Input::BUTTON_DOWN:
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_DOWN, true);
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_DOWN, true, dt);
					}
					break;

				case Input::BUTTON_LP:
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LP, true);					
					if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
						Client::getSingletonPtr()->sendInput(Input::BUTTON_LP, true, dt);
					}
					break;
				}
			}
		}
		
		// Process hard-coded keys.
		switch (e.key.keysym.sym){
		default:

			break;

		case SDLK_r:
			// Reload fighter settings.
			{
				Config c(Engine::getSingletonPtr()->getSettingsFile());
				m_pGUI.reset(new GUIGameState(Engine::getSingletonPtr()->getDataDirectory() +
					"/" + c.parseValue("GUI", "gamestate")));
			}
			StageManager::getSingletonPtr()->reload();
			PlayerManager::getSingletonPtr()->reload();
			break;

		case SDLK_p:
			PlayerManager::getSingletonPtr()->getRedPlayer()->toggleDrawHitboxes();
			PlayerManager::getSingletonPtr()->getBluePlayer()->toggleDrawHitboxes();
			break;

		case SDLK_k:
			m_pGUI->getWidgetPtr(GUIGameStateLayer::Root::HEALTHBAR_RED)->setPercent(75);
			break;

		case SDLK_t:
			if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
				RakNet::BitStream bit;
				bit.Write(static_cast<RakNet::MessageID>(NetMessage::SYSTEM_MESSAGE));
				RakNet::Time time = RakNet::GetTime();
				printf("Local time: %d\n", time);
				bit.Write(time);

				Client::getSingletonPtr()->send(bit, HIGH_PRIORITY, RELIABLE);
			}
			break;

		case SDLK_ESCAPE:
			
			m_quit = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP){
		// Process mapped buttons.
		// Red Player.
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED ||
			(Game::getSingletonPtr()->getMode() == Game::LOCAL &&
			PlayerManager::getSingletonPtr()->getRedPlayer()->getMode() == Player::Mode::LOCAL)){
			switch (PlayerManager::getSingletonPtr()->getRedPlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, false, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, false, dt);
				}
				break;

			case Input::BUTTON_UP:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_UP, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_UP, false, dt);
				}
				break;

			case Input::BUTTON_DOWN:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_DOWN, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_DOWN, false, dt);
				}
				break;

			case Input::BUTTON_LP:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LP, false);
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setReactivated(Input::BUTTON_LP, true);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LP, false, dt);
				}
				break;
			}
		}
		// Blue Player.
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE ||
				 (Game::getSingletonPtr()->getMode() == Game::LOCAL &&
				 PlayerManager::getSingletonPtr()->getBluePlayer()->getMode() == Player::Mode::LOCAL)){
			switch (PlayerManager::getSingletonPtr()->getBluePlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, false, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, false, dt);
				}
				break;

			case Input::BUTTON_UP:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_UP, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_UP, false, dt);
				}
				break;

			case Input::BUTTON_DOWN:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_DOWN, false);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_DOWN, false, dt);
				}
				break;

			case Input::BUTTON_LP:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LP, false);
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setReactivated(Input::BUTTON_LP, true);
				if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LP, false, dt);
				}
				break;
			}
		}
	}

	// Process gamepad input.
	if (e.type == SDL_CONTROLLERBUTTONDOWN){
		printf("[Gamepad Button ID]: %-5d(Gamepad ID: %d)\n", e.cbutton.button, e.cdevice.which);

		switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
		default:
			break;

		case Input::BUTTON_LEFT:
			player->getInput()->setButton(Input::BUTTON_LEFT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_RIGHT:
			player->getInput()->setButton(Input::BUTTON_RIGHT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;
		}
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP){
		switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
		default:
			break;

		case Input::BUTTON_LEFT:
			player->getInput()->setButton(Input::BUTTON_LEFT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_RIGHT:
			player->getInput()->setButton(Input::BUTTON_RIGHT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_START:
			m_quit = true;
			break;
		}
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION){
		// Process joystick information.
		Sint16 value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(1));
		const int deadzone = player->getInput()->getPadDeadzone();

		// First see if we should not process the joystick if the player is using the D-pad.
		if (player->getInput()->getMovementMode() == Input::MovementMode::DPAD){
			if (value < -deadzone || value > deadzone){
				player->getInput()->setMovementMode(Input::MovementMode::JOYSTICK);
			}
			else{
				value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(0));
				if (value < -deadzone || value > deadzone){
					player->getInput()->setMovementMode(Input::MovementMode::JOYSTICK);
				}
				else{
					// The joystick is not out of the deadzone, so remain in DPAD mode.
					return;
				}
			}
		}

		// Process Y-axis joystick movement.
		value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(1));
		if (value < -deadzone){
			player->getInput()->setButton(Input::BUTTON_UP, true);
		}
		else if (value > deadzone){
			player->getInput()->setButton(Input::BUTTON_DOWN, true);
		}
		else{
			player->getInput()->setButton(Input::BUTTON_UP, false);
			player->getInput()->setButton(Input::BUTTON_DOWN, false);
		}

		// Process X-axis joystick movement.
		value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(0));
		if (value < -deadzone){
			player->getInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (value > deadzone){
			player->getInput()->setButton(Input::BUTTON_RIGHT, true);
		}
		else{
			player->getInput()->setButton(Input::BUTTON_LEFT, false);
			player->getInput()->setButton(Input::BUTTON_RIGHT, false);
		}

		// TODO: Process GUI.
	}
}

// ================================================ //

void GameState::update(double dt)
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
		case SDL_KEYUP:
			this->handleInputDt(e, dt);
			break;

		case SDL_CONTROLLERDEVICEADDED:
			{
				int id = GamepadManager::getSingletonPtr()->addPad(e.cdevice.which);

				// Assign the new controller to the first open slot.
				if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
					PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(
						GamepadManager::getSingletonPtr()->getPad(id));
				}
				else if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
					PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(
						GamepadManager::getSingletonPtr()->getPad(id));
				}
			}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			// The player's pad pointer will be gone, so assign it to null to prevent undefined behavior.
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(nullptr);
			}
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(nullptr);
			}

			GamepadManager::getSingletonPtr()->removePad(e.cdevice.which);
			break;

		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			this->handleInputDt(e, dt);
			break;

		case SDL_CONTROLLERAXISMOTION:
			this->handleInputDt(e, dt);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	if (Game::getSingletonPtr()->getMode() == Game::SERVER){
		for (Server::getSingletonPtr()->m_packet = Server::getSingletonPtr()->m_peer->Receive();
			Server::getSingletonPtr()->m_packet;
			Server::getSingletonPtr()->m_peer->DeallocatePacket(Server::getSingletonPtr()->m_packet),
			Server::getSingletonPtr()->m_packet = Server::getSingletonPtr()->m_peer->Receive()){
			switch (Server::getSingletonPtr()->getPacket()->data[0]){
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

					// Send match over packet with proper victor.
					if (Server::getSingletonPtr()->m_packet->systemAddress == Server::getSingletonPtr()->m_redAddr){
						// Tell clients the player disconnected before sending match over packet.
						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
						bit.Write(username.c_str());
						Server::getSingletonPtr()->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);

						// Blue is victor now.
						Server::getSingletonPtr()->matchOver(Game::getSingletonPtr()->getBluePlayerName());
					}
					else if (Server::getSingletonPtr()->m_packet->systemAddress == Server::getSingletonPtr()->m_blueAddr){
						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
						bit.Write(username.c_str());
						Server::getSingletonPtr()->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);
						
						// Red is victor.
						Server::getSingletonPtr()->matchOver(Game::getSingletonPtr()->getRedPlayerName());
					}
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
					
					// Send match over packet with proper victor.
					if (Server::getSingletonPtr()->m_packet->systemAddress == Server::getSingletonPtr()->m_redAddr){
						// Tell clients the player lost connection before sending match over packet.
						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
						bit.Write(username.c_str());
						Server::getSingletonPtr()->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);

						// Blue is victor now.
						Server::getSingletonPtr()->matchOver(Game::getSingletonPtr()->getBluePlayerName());
					}
					else if (Server::getSingletonPtr()->m_packet->systemAddress == Server::getSingletonPtr()->m_blueAddr){
						RakNet::BitStream bit;
						bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
						bit.Write(username.c_str());
						Server::getSingletonPtr()->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);

						// Red is victor.
						Server::getSingletonPtr()->matchOver(Game::getSingletonPtr()->getRedPlayerName());
					}
				}
				break;

			case NetMessage::SYSTEM_MESSAGE:
				{
					RakNet::BitStream bit(Server::getSingletonPtr()->getPacket()->data,
									  Server::getSingletonPtr()->getPacket()->length,
									  false);
					bit.IgnoreBytes(sizeof(RakNet::MessageID));
					RakNet::Time time;
					bit.Read(time);

					printf("Client time: %d\n", time);
				}
				break;

			case NetMessage::CLIENT_INPUT:
				// Verify this message is from a playing client (not spectating).
				if (Server::getSingletonPtr()->getPacket()->systemAddress == Server::getSingletonPtr()->m_redAddr ||
					Server::getSingletonPtr()->getPacket()->systemAddress == Server::getSingletonPtr()->m_blueAddr){
					// Read in the NetInput struct from client.
					RakNet::BitStream bit(Server::getSingletonPtr()->getPacket()->data, 
						Server::getSingletonPtr()->getPacket()->length, false);
					bit.IgnoreBytes(sizeof(RakNet::MessageID));
					Client::NetInput netInput;
					bit.Read(netInput);
					Uint32 stageShiftSeq = Server::getSingletonPtr()->m_lastProcessedStageShift;
					bit.Read(stageShiftSeq);
					Server::getSingletonPtr()->m_lastProcessedStageShift = stageShiftSeq;
					
					// Apply the NetInput struct to the proper player.
					if (Server::getSingletonPtr()->validateInput(netInput)){
						if (Server::getSingletonPtr()->getPacket()->systemAddress == Server::getSingletonPtr()->m_redAddr){
							PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(netInput.input, netInput.value);
							if (netInput.value == false){
								PlayerManager::getSingletonPtr()->getRedPlayerInput()->setReactivated(netInput.input, true);
							}
							// Note: I previously processed input and applied it ONLY here, and didn't call Player::update()
							// in PlayerManager::update(). I don't remember the exact reason, but now I do the opposite.
							Server::getSingletonPtr()->m_redLastProcessedInput = netInput.seq;
						}
						else if (Server::getSingletonPtr()->getPacket()->systemAddress == Server::getSingletonPtr()->m_blueAddr){
							PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(netInput.input, netInput.value);
							if (netInput.value == false){
								PlayerManager::getSingletonPtr()->getBluePlayerInput()->setReactivated(netInput.input, true);
							}
							Server::getSingletonPtr()->m_blueLastProcessedInput = netInput.seq;
						}
					}
				}
				break;
			}
		}

		// Broadcast player updates to all client.
		//if (m_pServerUpdateTimer->getTicks() > 1000){
			Server::getSingletonPtr()->updatePlayers();
		//	m_pServerUpdateTimer->restart();
		//}
		//Server::getSingletonPtr()->sendLastProcessedInput();
	}
	else if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getButton(Input::BUTTON_LEFT) == true){
				Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
			}
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getButton(Input::BUTTON_RIGHT) == true){
				Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
			}
		}
		else if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE){
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getButton(Input::BUTTON_LEFT) == true){
				Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
			}
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getButton(Input::BUTTON_RIGHT) == true){
				Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
			}
		}

		//printf("%d unprocessed inputs / %d\n", Client::getSingletonPtr()->m_pendingInputs.size(), 
			//(Client::getSingletonPtr()->m_pendingInputs.size() == 0) ? 0 : Client::getSingletonPtr()->m_pendingInputs.front().seq);

		for (Client::getSingletonPtr()->m_packet = Client::getSingletonPtr()->m_peer->Receive();
			Client::getSingletonPtr()->m_packet;
			Client::getSingletonPtr()->m_peer->DeallocatePacket(Client::getSingletonPtr()->m_packet),
			Client::getSingletonPtr()->m_packet = Client::getSingletonPtr()->m_peer->Receive()){
			if (Client::getSingletonPtr()->update() == false){
				switch (Client::getSingletonPtr()->getPacket()->data[0]){
				default:
					break;

				case NetMessage::UPDATE_RED_PLAYER:
					if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
							Client::getSingletonPtr()->getPacket()->length, false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Server::PlayerUpdate update;
						bit.Read(update);
						PlayerManager::getSingletonPtr()->getRedPlayer()->updateFromServer(update);
					}
					break;

				case NetMessage::UPDATE_BLUE_PLAYER:

					break;

				case NetMessage::UPDATE_PLAYERS:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
							Client::getSingletonPtr()->getPacket()->length, false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Server::PlayerUpdate red;
						bit.Read(red);
						Server::PlayerUpdate blue;
						bit.Read(blue);

						// If this client is playing, enqueue this input for processing.
						if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
							PlayerManager::getSingletonPtr()->getRedPlayer()->updateFromServer(red);
						}
						// Otherwise, update player directly.
						else{
							Player* redPlayer = PlayerManager::getSingletonPtr()->getRedPlayer();
							redPlayer->setPosition(red.x, red.y);
							redPlayer->setCurrentState(red.state);

							// Re-apply player shifts.
							for (std::list<Client::StageShift>::iterator itr = Client::getSingletonPtr()->m_pendingStageShifts.begin();
								 itr != Client::getSingletonPtr()->m_pendingStageShifts.end();
								 ++itr){
								SDL_Rect pos = redPlayer->getPosition();
								pos.x += itr->playerShift;
								redPlayer->setPosition(pos);
							}
						}
						
						if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE){
							PlayerManager::getSingletonPtr()->getBluePlayer()->updateFromServer(blue);
						}
						else{
							Player* bluePlayer = PlayerManager::getSingletonPtr()->getBluePlayer();
							bluePlayer->setPosition(blue.x, blue.y);
							bluePlayer->setCurrentState(blue.state);

							// Re-apply player shifts.
							for (std::list<Client::StageShift>::iterator itr = Client::getSingletonPtr()->m_pendingStageShifts.begin();
								 itr != Client::getSingletonPtr()->m_pendingStageShifts.end();
								 ++itr){
								SDL_Rect pos = bluePlayer->getPosition();
								pos.x += itr->playerShift;
								bluePlayer->setPosition(pos);
							}
						}
					}
					break;

				case NetMessage::STAGE_SHIFT:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
											  Client::getSingletonPtr()->getPacket()->length,
											  false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Stage::ShiftUpdate update;
						bit.Read(update);
						StageManager::getSingletonPtr()->getStage()->updateShiftFromServer(update);
					}
					break;

				case NetMessage::LAST_PROCESSED_INPUT_SEQUENCE:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
											  Client::getSingletonPtr()->getPacket()->length, 
											  false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Uint32 lastProcessedInput = 0;
						bit.Read(lastProcessedInput);
						for (Client::ClientInputList::iterator itr = Client::getSingletonPtr()->m_pendingInputs.begin();
							itr != Client::getSingletonPtr()->m_pendingInputs.end();){
							if (itr->seq <= lastProcessedInput){
								itr = Client::getSingletonPtr()->m_pendingInputs.erase(itr);
							}
							else{
								++itr;
							}
						}
					}
					break;

				case NetMessage::RED_TAKE_HIT:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
											  Client::getSingletonPtr()->getPacket()->length,
											  false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Uint32 damage = 0, stun = 0;
						bit.Read(damage);
						bit.Read(stun);
						PlayerManager::getSingletonPtr()->getRedPlayer()->takeHit(damage, stun);
					}
					break;

				case NetMessage::BLUE_TAKE_HIT:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
											  Client::getSingletonPtr()->getPacket()->length,
											  false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						Uint32 damage = 0, stun = 0;
						bit.Read(damage);
						bit.Read(stun);
						PlayerManager::getSingletonPtr()->getBluePlayer()->takeHit(damage, stun);
					}
					break;

				case NetMessage::MATCH_OVER:
					{
						RakNet::BitStream bit(Client::getSingletonPtr()->getPacket()->data,
											  Client::getSingletonPtr()->getPacket()->length, 
											  false);
						bit.IgnoreBytes(sizeof(RakNet::MessageID));

						RakNet::RakString victor;
						bit.Read(victor);
						printf("%s wins!\n", victor.C_String());
						m_quit = true;
					}
					break;
				}
			}
		}
	}

	// Update and render all game objects and players.
	StageManager::getSingletonPtr()->update(dt);
	m_pObjectManager->update(dt);
	m_pGUI->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //