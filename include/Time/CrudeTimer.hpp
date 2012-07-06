#ifndef CRUDETIMER_HPP
#define CRUDETIMER_HPP

#include <boost/timer.hpp>

#include <misc/singleton.hpp>

#define Clock Singleton < CrudeTimer >::Instance()

class CrudeTimer
{

  public:

    /*!
     * returns how much time has elapsed since the timer was started
     *
     * @return
     */
    double GetCurrentTime()
    {
      return (double) timer.elapsed();
    }
    void restart()
    {
      timer.restart();
    }
  private:

    boost::timer timer;

};

#endif // CRUDETIMER_HPP
