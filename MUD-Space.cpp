#include "MUD-Space.h"
#include "Server.h"
#include "Game.h"

#include <iostream>
#include <exception>
#include <thread>

using namespace std;

int main()
{
	const unsigned short port = 4000;

	try {
		boost::asio::io_context io_context;
		Server server(io_context, port);

		cout << "MUD-Space starting on port " << port << endl;
		server.start_accept();
		std::thread game_thread([&]() {
			Game game;
			game.run();
			io_context.stop();
		});
		io_context.run();
		game_thread.join();
	}
	catch (const exception& e) {
		cerr << "Fatal: " << e.what() << endl;
		return 1;
	}

	return 0;
}
