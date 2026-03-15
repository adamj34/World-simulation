

class ISimulationCommand {
public:
    virtual ~ISimulationCommand() = default;
    virtual void execute() = 0;
};