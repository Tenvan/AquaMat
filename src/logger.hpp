//
// Created by ralf on 03.01.22.
//

#ifndef AQUAMAT_LOGGER_HPP
#define AQUAMAT_LOGGER_HPP

void printLogLevel(Print *_logOutput, int logLevel);
void printPrefix(Print *_logOutput, int logLevel);
void printSuffix(Print *_logOutput, int logLevel);
void printTimestamp(Print *_logOutput);
void setupLogger();

#endif //AQUAMAT_LOGGER_HPP
