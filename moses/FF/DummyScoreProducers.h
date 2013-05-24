// $Id$

#ifndef moses_DummyScoreProducers_h
#define moses_DummyScoreProducers_h

#include "StatelessFeatureFunction.h"
#include "StatefulFeatureFunction.h"
#include "util/check.hh"

namespace Moses
{

class WordsRange;

/** Calculates Distortion scores
 */
class DistortionScoreProducer : public StatefulFeatureFunction
{
public:
	DistortionScoreProducer(const std::string &line)
	: StatefulFeatureFunction("Distortion", 1, line)
	{}

  static float CalculateDistortionScore(const Hypothesis& hypo,
                                 const WordsRange &prev, const WordsRange &curr, const int FirstGapPosition);

  virtual const FFState* EmptyHypothesisState(const InputType &input) const;

  virtual FFState* Evaluate(
    const Hypothesis& cur_hypo,
    const FFState* prev_state,
    ScoreComponentCollection* accumulator) const;

  virtual FFState* EvaluateChart(
    const ChartHypothesis& /* cur_hypo */,
    int /* featureID - used to index the state in the previous hypotheses */,
    ScoreComponentCollection*) const {
		CHECK(0); // feature function not valid in chart decoder
		return NULL;
	}
};

/** Doesn't do anything but provide a key into the global
 *  score array to store the word penalty in.
 */
class WordPenaltyProducer : public StatelessFeatureFunction
{
public:
	WordPenaltyProducer(const std::string &line) : StatelessFeatureFunction("WordPenalty",1, line) {}

  virtual void Evaluate(
    const PhraseBasedFeatureContext& context,
  	ScoreComponentCollection* accumulator) const
  {}

  virtual void EvaluateChart(
    const ChartBasedFeatureContext& context,
    ScoreComponentCollection* accumulator) const
    {
      //required but does nothing.
    }

  virtual void Evaluate(const TargetPhrase &targetPhrase
                      , ScoreComponentCollection &scoreBreakdown
                      , ScoreComponentCollection &estimatedFutureScore) const;

};

/** unknown word penalty */
class UnknownWordPenaltyProducer : public StatelessFeatureFunction
{
public:
	UnknownWordPenaltyProducer(const std::string &line)
  : StatelessFeatureFunction("UnknownWordPenalty",1, line)
  {
	  m_tuneable = false;
  }

};

}

#endif