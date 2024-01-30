#include <iostream>
#include "map.h"
#include "task.h"
#include "cbs.h"
#include "xml_logger.h"

int main(int argc, const char *argv[])
{
    Config config;
    if(argc > 1)
        config.getConfig(argv[1]);
    else
        config.getConfig("config.xml");
    Map map = Map(config.agent_size);
    std::string map_name = "map.xml";
    map.get_map(map_name.c_str());
    PHeuristic h_values;
    h_values.init(map.get_width(), map.get_height());
    h_values.count(map);

    Task task;
    task.get_task("task.xml");
    task.make_ids(map.get_width());
    CBS cbs;
    Solution solution = cbs.find_solution(map, task, config, h_values);
    auto found = solution.found?"true":"false";
    std::cout<<"Soulution found: " << found << "\nRuntime: "<<solution.time.count() << "\nMakespan: " << solution.makespan << "\nFlowtime: " << solution.flowtime<< "\nInitial Cost: "<<solution.init_cost<< "\nCollision Checking Time: " << solution.check_time
              << "\nHL expanded: " << solution.high_level_expanded << "\nLL searches: " << solution.low_level_expansions << "\nLL expanded(avg): " << solution.low_level_expanded << std::endl;

    XML_logger logger;
    logger.get_log(map_name.c_str());
    logger.write_to_log_summary(solution);
    logger.write_to_log_path(solution, map);
    logger.save_log();

    return 0;
}
