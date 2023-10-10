void EEPROM_Erase_and_Write1B(uint16_t addr, uint8_t data)
{
  while(EECR & (1<<EEPE)) ; 
  EECR = 0x00;      
  EEAR = addr;      
  EEDR = data;      
  char backupSREG;    
  backupSREG = SREG;   
  cli();        
  EECR |= (1<<EEMPE);  
  EECR |= (1<<EEPE);    
  SREG = backupSREG;    
}



void EEPROM_Erase_only(uint16_t addr)
{  
  while(EECR & (1<<EEPE)) ; 
  EECR = 0b01 << EEPM0;   
  EEAR = addr;      
  EEDR = 0xFF;      
  char backupSREG; 
  backupSREG = SREG;  
  cli();       
  EECR |= (1<<EEMPE);  
  EECR |= (1<<EEPE);    
  SREG = backupSREG;   
}


void EEPROM_Write_to_Empty_location(uint16_t addr, uint8_t data)
{
  while(EECR & (1<<EEPE)) ; 
  EECR = 0b10 << EEPM0;    
  EEAR = addr;      
  EEDR = data;      
  char backupSREG;    
  backupSREG = SREG;    
  cli();        
  EECR |= (1<<EEMPE);   
  EECR |= (1<<EEPE);    
  SREG = backupSREG;    
}




unsigned char EEPROM_read1byte(uint16_t addr)  
{       
  while (EECR & (1<<EEPE)) ;   
  EEAR = addr;        
  EECR |= (1<<EERE);      
  return EEDR;        
}


void display_all_data_in_EEPROM()
{
  Serial.println("Data in the EEPROM");
  int i;
  uint8_t c;
  for (i=0;i<1024;i++)
  {
    c = EEPROM_read1byte(i);
    if( (i>0) && (i%16==0) )
        Serial.println("");
    Serial.print(c);
    Serial.print(" ");
  }
  Serial.println("\n\r--------------------------");  
}


void update_if_data_changed(uint16_t addr, uint8_t data)
{
  uint8_t x;
  x = EEPROM_read1byte(addr);
  if (x!=data)
    EEPROM_Erase_and_Write1B(addr, data);
}

void Scan_all_data_in_EEPROM() {
  uint16_t i;
  uint8_t d; 
  uint8_t found = 0;
  for (i=0;i<1024;i++)
  {
    d = EEPROM_read1byte(i);
    if (d != 0xFF) {
      found++;
      Serial.print("found data ");
      Serial.print(d);
      Serial.print(" on address ");
      Serial.print("[");
      Serial.print(i);
      Serial.println("]");
    }
  }
  if (found == 0) Serial.println("No data found");
}

void EEPROM_clear_all_data() {
  for (uint16_t i = 0; i<1024; i++) EEPROM_Erase_only(i);
}

void EEPROM_first_write_alarm_time(uint8_t hour, uint8_t minute) {
  EEPROM_Write_to_Empty_location(1, minute);
  EEPROM_Write_to_Empty_location(0, hour);
}

//***************************Wear level write***************************
void EEPROM_scan_previous_and_write_alarm_time(uint8_t hour, uint8_t minute) {
  uint16_t i, data_location;
  uint8_t data;
  for (i=0; i<1024; i++) {
    data = EEPROM_read1byte(i);
    if (data != 0xFF) {
      // If data Scanned on address 0
      if (i == 0) {
        data = EEPROM_read1byte(1023);
        // If data is first scanned on address 0 
        // And data is sccaned on address 1023
        // So It's Hour data on address 1023
        if (data != 0xFF) {
          //Write Hour on address 1022
          data_location = 1023;
          EEPROM_Erase_only(data_location); //delete previous data before write
          data_location = (data_location + 1023) % 1024;
          EEPROM_Write_to_Empty_location(data_location, hour);
          //Write Minute on address 1023
          data_location = i;
          EEPROM_Erase_only(data_location); //delete previous data before write
          data_location = (data_location + 1023) % 1024;
          EEPROM_Write_to_Empty_location(data_location, minute);
          i = 1024;
        // If data is first scanned on address 0
        // But none data on address 1023
        // So It's Hour data on address 0
        } else {
          //Write Hour on address 1023
          data_location = i;
          EEPROM_Erase_only(data_location); //delete previous data before write
          data_location = (data_location + 1023) % 1024;
          EEPROM_Write_to_Empty_location(data_location, hour);
          //Write Minute on address 0
          data_location = (i+1) % 1024;
          EEPROM_Erase_only(data_location); //delete previous data before write
          data_location = (data_location + 1023) % 1024;
          EEPROM_Write_to_Empty_location(data_location, minute);
          i = 1024;
        }
      // If data Scanned any adress except adrees 0
      } else {
      //Write Hour
      data_location = i;
      EEPROM_Erase_only(data_location); //delete previous data before write
      data_location = (data_location + 1023) % 1024;
      EEPROM_Write_to_Empty_location(data_location, hour);
      //Write Minute
      data_location = (i+1) % 1024;
      EEPROM_Erase_only(data_location); //delete previous data before write
      data_location = (data_location + 1023) % 1024;
      EEPROM_Write_to_Empty_location(data_location, minute);
      i = 1024;
      }
    }
  }
}

uint8_t read_hour_alarm_time_in_EEPROM() {
  uint8_t data;
  uint16_t i;
  for (i=0; i<1024; i++) {
    data = EEPROM_read1byte(i);
    if (data != 0xFF) {
      // If data Scanned on address 0
      if (i == 0) {
        data = EEPROM_read1byte(1023);
        // If data is first scanned on address 0 
        // And data is sccaned on address 1023
        // So It's Hour data on address 1023
        if (data != 0xFF)
          return data;
        // If data is first scanned on address 0
        // But none data on address 1023
        // So It's Hour data on address 0
        else {
          data = EEPROM_read1byte(i);
          return data;
        }
      // If data Scanned any adress except adrees 0
      } else return data;
    }
  }
}

uint8_t read_minute_alarm_time_in_EEPROM() {
  uint8_t data;
  uint16_t i;
  for (i=0; i<1024; i++) {
    data = EEPROM_read1byte(i);
    if (data != 0xFF) {
      // If data Scanned on address 0
      if (i == 0) {
        data = EEPROM_read1byte(1023);
        // If data is first scanned on address 0 
        // And data is sccaned on address 1023
        // So It's Minute data on address 0
        if (data != 0xFF) {
          data = EEPROM_read1byte(i);
          return data;
        }
        // If data is first scanned on address 0
        // But none data on address 1023
        // So It's Minute data on address 1
        else {
          data = EEPROM_read1byte(i+1);
          return data;
        }
      // If data Scanned any adress except adrees 0
      } else {
        data = EEPROM_read1byte(i+1);
        return data;
      }
    }
  }
}