#pragma once

class Command
{
public:
	Command(const std::string& argName)
		: m_bridge(nullptr)
		, m_shouldExecute(false)
		, m_argumentName("-" + argName)
	{

	}

	virtual void Execute() = 0;

	HueBridge* GetBridge() const		{ return m_bridge; }
	void SetBridge(HueBridge* bridge)	{ m_bridge = bridge; }

	void FlagForExecution() { m_shouldExecute = true; }
	bool ShouldExecute() const { return m_shouldExecute; }

	const std::string& GetString() const { return m_argumentName; }

protected:
	HueBridge* m_bridge;

private:
	bool m_shouldExecute;
	std::string m_argumentName;
};
