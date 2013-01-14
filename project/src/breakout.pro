######################################################################
# Automatically generated by qmake (2.01a) Fri Nov 2 02:04:49 2012
######################################################################

breakout {
	QMAKE_CC = g++-4.7
	QMAKE_CXX = g++-4.7
	QMAKE_CXXFLAGS += -O3 -std=c++11 -Wall -Wfatal-errors
	TEMPLATE = app
	TARGET = 
	DEPENDPATH += . impl
	INCLUDEPATH += . impl

	# Input
	HEADERS +=	Ball.hpp \
				Body.hpp \
				Box.hpp \
				BreakoutApp.hpp \
				BreakoutFrame.hpp \
				BreakoutWorld.hpp \
				Circle.hpp \
				Contact.hpp \
				Drawable.hpp \
				World.hpp \
				Movable.hpp \
				Paddle.hpp \
				Point.hpp \
				Vector.hpp \
				impl/Ball.hpp \
				impl/Body.hpp \
				impl/Box.hpp \
				impl/BreakoutApp.hpp \
				impl/BreakoutFrame.hpp \
				impl/BreakoutWorld.hpp \
				impl/Circle.hpp \
				impl/Contact.hpp \
				impl/Drawable.hpp \
				impl/World.hpp \
				impl/Movable.hpp \
				impl/Paddle.hpp \
				impl/Vector.hpp

	SOURCES += impl.cpp jsoncpp/json_reader.cpp jsoncpp/json_writer.cpp jsoncpp/json_value.cpp main.cpp

}

test {
	QMAKE_CC = g++-4.7
	QMAKE_CXX = g++-4.7
	QMAKE_CXXFLAGS += -std=c++11 -Wall -Wfatal-errors
	TEMPLATE = app
	TARGET = test
	DEPENDPATH += . impl
	INCLUDEPATH += . impl

	# Input
	HEADERS +=	Ball.hpp \
				Body.hpp \
				Box.hpp \
				BreakoutApp.hpp \
				BreakoutFrame.hpp \
				BreakoutWorld.hpp \
				Circle.hpp \
				Contact.hpp \
				Drawable.hpp \
				World.hpp \
				Movable.hpp \
				Paddle.hpp \
				Point.hpp \
				Vector.hpp \
				impl/Ball.hpp \
				impl/Body.hpp \
				impl/Box.hpp \
				impl/BreakoutApp.hpp \
				impl/BreakoutFrame.hpp \
				impl/BreakoutWorld.hpp \
				impl/Circle.hpp \
				impl/Contact.hpp \
				impl/Drawable.hpp \
				impl/World.hpp \
				impl/Movable.hpp \
				impl/Paddle.hpp \
				impl/Vector.hpp

	SOURCES += impl.cpp jsoncpp/json_reader.cpp jsoncpp/json_writer.cpp jsoncpp/json_value.cpp test.cpp	
}
