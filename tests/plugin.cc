#include <clap/helpers/host-proxy.hxx>
#include <clap/helpers/param-queue.hh>
#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>
#include <clap/helpers/reducing-param-queue.hh>
#include <clap/helpers/reducing-param-queue.hxx>

#include <catch2/catch_all.hpp>

template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::Maximal>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::Minimal>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                     clap::helpers::CheckingLevel::None>;
template class clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                                     clap::helpers::CheckingLevel::Maximal>;

template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::Maximal>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::Minimal>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Terminate,
                                        clap::helpers::CheckingLevel::None>;
template class clap::helpers::HostProxy<clap::helpers::MisbehaviourHandler::Ignore,
                                        clap::helpers::CheckingLevel::Maximal>;

CATCH_TEST_CASE("Plugin - Link") {
   clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                         clap::helpers::CheckingLevel::Maximal> *p0 = nullptr;
   clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                         clap::helpers::CheckingLevel::Minimal> *p1 = nullptr;
   clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                         clap::helpers::CheckingLevel::None> *p2 = nullptr;
   clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                         clap::helpers::CheckingLevel::Maximal> *p3 = nullptr;
}
