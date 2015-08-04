/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#ifndef STM32PLUS_F4
#error This class can only be used with the STM32F4 series
#endif


namespace stm32plus {


  /**
   * Basic features for the internal flash peripheral
   */

  class InternalFlashPeripheral {

    protected:
      const uint8_t *_sizeMap;

    public:
      InternalFlashPeripheral(const uint8_t *sizeMap);

      uint8_t getPageFromAddress(uint32_t flashAddress) const;
      uint32_t getPageSize(uint32_t flashAddress) const;
      bool isStartOfPage(uint32_t address) const;
  };


  /**
   * Constructor
   * @param sizeMap pointer to the sector size map
   */

  inline InternalFlashPeripheral::InternalFlashPeripheral(const uint8_t *sizeMap)
    : _sizeMap(sizeMap) {
  }


  /**
   * Get the page size of this device
   * @return The page size
   */

  inline uint32_t InternalFlashPeripheral::getPageSize(uint32_t flashAddress) const {
    return _sizeMap[getPageFromAddress(flashAddress)]*1024;
  }


  /**
   * Get the page number from the flash address
   * @param flashAddress
   * @return the zero-based page number
   */

  inline uint8_t InternalFlashPeripheral::getPageFromAddress(uint32_t flashAddress) const {

    uint8_t pageNumber;
    uint32_t address,pageSize;

    address=FLASH_BASE;
    pageNumber=0;

    for(;;) {

      pageSize=getPageSize(address);

      if(flashAddress<address+pageSize)
        return pageNumber;

      pageNumber++;
      address+=pageSize;
    }
  }


  /**
   * Check if this address is at the start of a page
   * @param address The address to check
   * @return true if it's at the start of a page
   */

  inline bool InternalFlashPeripheral::isStartOfPage(uint32_t addressToCheck) const {

    uint32_t address;

    address=FLASH_BASE;

    while(addressToCheck>=address)
      address+=getPageSize(address);

    return address==addressToCheck;
  }
}
