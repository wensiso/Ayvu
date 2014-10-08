/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bb/cascades/Application>
#include <bb/device/Led>

#include <QLocale>
#include <QTranslator>
#include "applicationui.hpp"

#include <Qt/qdeclarativedebug.h>
#include <iostream>

#include <audiocontrol.h>

using namespace bb::cascades;

namespace ayvu {
    qint64 clock_skew = 0;
}

static void customMessageHandler(QtMsgType type, const char *message)
{
	switch (type) {
		case QtDebugMsg:
			std::cout << "Debug: " << message << std::endl;
			break;
		case QtWarningMsg:
			std::cout << "Warning: " << message << std::endl;
			break;
		case QtCriticalMsg:
			std::cout << "Critical: " << message << std::endl;
			break;
		case QtFatalMsg:
			std::cout << "Fatal: " << message << std::endl;
			std::abort();
			break;
	}
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
	qInstallMsgHandler(customMessageHandler);

	qmlRegisterType<bb::device::Led>("bb.device", 1, 0, "Led");
	qmlRegisterUncreatableType<bb::device::LedColor>("bb.device", 1, 0, "LedColor", "");

	qmlRegisterType<ayvu::AudioControl>("ayvu.audio", 1, 0, "AudioControl");

    Application app(argc, argv);

    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    new ApplicationUI(&app);


    // Enter the application main event loop.
    return Application::exec();
}
