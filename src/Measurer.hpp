#ifndef MEASURER_HPP
#define MEASURER_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>

class Measurer
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		std::string measure;
		int cachedTime;
		Configuration::Channels cachedChannel;
		Configuration::Measures cachedMeasure;
	
	public:
		Measurer(Configuration& configuration, State& state, Samples& samples);
		std::string getMeasure(void);
	
	private:
		std::string getMean(void);
		std::string getPeak(void);
		std::string getRMS(void);
		std::string getFrequency(void);
		std::string getPeriod(void);
		std::string getRiseTime(void);
		std::string getFallTime(void);
		std::string getDutyCycle(void);
		std::string getPhase(void);
		std::string getRatio(void);
		float maximum(const std::vector<float>& signal);
		float minimum(const std::vector<float>& signal);
		int getMaxCorrelation(const std::vector<float>& signalA, const std::vector<float>& signalB);
};

#endif
