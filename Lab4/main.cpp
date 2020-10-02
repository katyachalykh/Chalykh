//#include <cstdint>            //for int types such as uint32_t
#include "gpioaregisters.hpp" //for Gpioa
#include "gpiocregisters.hpp" //for Gpioc
#include "gpiobregisters.hpp" //for Gpiob
#include "rccregisters.hpp"   //for RCC
#include "tim2registers.hpp"   //for SPI2
#include "nvicregisters.hpp"  //for NVIC

using namespace std ;



extern "C"
{
int __low_level_init(void)
{
  //Switch on external 16 MHz oscillator
  RCC::CR::HSEON::On::Set() ;
  while (!RCC::CR::HSERDY::Ready::IsSet())
  {

  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hse::Set() ;
  while (!RCC::CFGR::SWS::Hse::IsSet())
  {

  }
  
  
  //Switch on clock on PortA and PortC, PortB
  RCC::AHB1ENRPack<
    RCC::AHB1ENR::GPIOCEN::Enable,
    RCC::AHB1ENR::GPIOAEN::Enable
    >::Set() ;
  
  RCC::APB1ENRPack<
    RCC::APB1ENR::TIM2EN::Enable,  
    >::Set() ;
  
  // LED1 on PortA.5, set PortA.5 as output
  GPIOA::MODER::MODER5::Output::Set() ;
      
  
  // LED2 on PortC.9, LED3 on PortC.8, LED4 on PortC.5 so set PortC.5,8,9 as output
  GPIOC::MODERPack<
    GPIOC::MODER::MODER5::Output,
    GPIOC::MODER::MODER8::Output,
    GPIOC::MODER::MODER9::Output
  >::Set() ;
      

  return 1;
}
}

int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  GPIOC::MODER::MODER5::Output::Set() ;
  GPIOC::ODR::ODR5::High::Set() ;
  GPIOC::ODR::ODR5::Low::Set() ;
  return 0 ;
}

