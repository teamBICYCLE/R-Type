/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Manager.hh"

namespace Input {
    Manager::Manager()
   {
   }

   Manager::~Manager()
   {
   }

   std::vector<Data>    Manager::getInputs()
   {
       std::vector<Data> ret;

       for (auto & config : _configs) {
           Data input = config.getInput();

            ret.push_back(config.getInput());
       }
       return ret;
   }
}
