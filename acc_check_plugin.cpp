#include <eosio/acc_check_plugin/acc_check_plugin.hpp>

namespace eosio {
	static appbase::abstract_plugin& _acc_check_plugin = app().register_plugin<acc_check_plugin>();

	class acc_check_plugin_impl {
	};

	acc_check_plugin::acc_check_plugin() {}
	acc_check_plugin::~acc_check_plugin() {}

	void acc_check_plugin::set_program_options(options_description&, options_description& cfg) {}

	void acc_check_plugin::plugin_initialize(const variables_map& options) {}

	void acc_check_plugin::plugin_startup() {
		ilog("starting acc_check_plugin");
		app().get_plugin<http_plugin>().add_api({
			{"/v1/chain-ext/get_accounts", [&](std::string url, std::string body, url_response_callback callback) {
				try {
					auto api = app().get_plugin<chain_plugin>().get_read_only_api();
					if (body.empty()) body = "{}";
					std::vector<fc::variant> results;
					fc::variant var = fc::json::from_string(body).get_object();
					bool verbose = var["verbose"].as_bool();
					auto accounts = var["accounts"].get_array();
					for (auto it = accounts.begin(); it != accounts.end(); it++) {
						try {
							auto info = api.get_account(chain_apis::read_only::get_account_params{it->as_string()});
							if (verbose) {
								results.push_back(fc::variant(info));
							} else {
								results.push_back(fc::variant(true));
							}
						} catch (...) {
							if (verbose) {
								results.push_back(fc::variant());
							} else {
								results.push_back(fc::variant(false));
							}
						}
					}
					callback(200, fc::json::to_string(results));
				} catch (...) {
					http_plugin::handle_exception("chain-ext", "get_accounts", body, callback);
				}
			}}
		});
	}

	void acc_check_plugin::plugin_shutdown() {}
}
