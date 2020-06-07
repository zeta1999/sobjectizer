/*
 * A very simple test case for searching event handlers in parent states.
 */

#include <iostream>

#include <so_5/all.hpp>

#include <test/3rd_party/various_helpers/time_limited_execution.hpp>

class a_test_t final : public so_5::agent_t
{
	struct sig_0 final : public so_5::signal_t {};
	struct sig_1 final : public so_5::signal_t {};
	struct sig_2 final : public so_5::signal_t {};
	struct sig_3 final : public so_5::signal_t {};

	state_t st_parent{ initial_substate_of{ so_default_state() }, "parent" };
	state_t st_child_1{ initial_substate_of{ st_parent }, "child_1" };
	state_t st_child_2{ initial_substate_of{ st_child_1 }, "child_2" };

public :
	a_test_t( context_t ctx )
		:	so_5::agent_t{ ctx }
	{
		this >>= st_child_2;

		so_default_state().event( [this](mhood_t< sig_0 > ) {
				std::cout << "--- sig_0 handler from st_default ---" << std::endl;
				so_5::send< sig_1 >( *this );
			} );
		st_parent.event( [this](mhood_t< sig_1 >) {
				std::cout << "--- sig_1 handler from st_parent ---" << std::endl;
				so_5::send< sig_2 >( *this );
			} );
		st_child_1.event( [this](mhood_t< sig_2 >) {
				std::cout << "--- sig_2 handler from st_child_1 ---" << std::endl;
				so_5::send< sig_3 >( *this );
			} );
		st_child_2.event( [this](mhood_t< sig_3 >) {
				std::cout << "--- sig_3 handler from st_child_2 ---" << std::endl;
				so_deregister_agent_coop_normally();
			} );
	}

	virtual void
	so_evt_start() override
	{
		std::cout << so_current_state().query_name() << std::endl;

		so_5::send< sig_0 >( *this );
	}
};

int
main()
{
	try
	{
		run_with_time_limit(
			[]()
			{
				so_5::launch( []( so_5::environment_t & env ) {
						env.introduce_coop( []( so_5::coop_t & coop ) {
								coop.make_agent< a_test_t >();
							} );
					}/*,
					[]( so_5::environment_params_t & params ) {
						params.message_delivery_tracer(
								so_5::msg_tracing::std_cout_tracer() );
					}*/ );
			},
			20,
			"simple test for event handlers from parent state" );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

