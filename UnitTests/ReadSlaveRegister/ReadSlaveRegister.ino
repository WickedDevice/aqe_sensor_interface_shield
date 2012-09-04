
#include <Wire.h>

#define  MAX_RESPONSE_LENGTH            (16)  
#define  CMD_READ                       (0x11)
uint8_t  SLAVE_ADDRESS                = (0x03);

// BASE ADDRESSES
#define METADATA_BASE_OFFSET             (0)
#define SENSOR_DATA_BASE_OFFSET          (32)
#define SENSOR_DATA_ADDRESS_BLOCK_SIZE  (256)      
#define DEBUG_BASE_OFFSET                (65408)

// METADATA FIELD OFFSETS
#define METADATA_SENSOR_COUNT_FIELD_OFFSET (0)
#define METADATA_MODULE_ID_FIELD_OFFSET    (1)
#define METADATA_VERSION_FIELD_OFFSET      (7)

// SENSOR DATA FIELD OFFSETS
#define SENSOR_TYPE_FIELD_OFFSET                  (0)
#define SENSOR_UNITS_FIELD_OFFSET                 (16)
#define SENSOR_R0_FIELD_OFFSET                    (32)
#define SENSOR_COMPUTED_VALUE_FIELD_OFFSET        (36)
#define SENSOR_UNITS_MULTIPLIER_FIELD_OFFSET      (40)
#define SENSOR_RAW_VALUE_FIELD_OFFSET             (44)
#define SENSOR_RAW_VALUE_SENSED_RESISTANCE_OFFSET (48)

// DEBUG DATA FIELD OFFSETS
#define DEBUG_NO2_HEATER_V_PLUS              (0)
#define DEBUG_NO2_HEATER_V_MINUS             (4)
#define DEBUG_NO2_HEATER_POWER_MW            (8)
#define DEBUG_NO2_DIGIPOT_VALUE             (12)
#define DEBUG_CO_HEATER_V_PLUS              (16)
#define DEBUG_CO_HEATER_V_MINUS             (20)
#define DEBUG_CO_HEATER_POWER_MW            (24)
#define DEBUG_CO_DIGIPOT_VALUE              (28)
#define DEBUG_DIGIPOT_STATUS                (32)

uint8_t  buffer[MAX_RESPONSE_LENGTH];          // temporary storage for the slave device responses

uint16_t addresses_to_read[] = {
 METADATA_BASE_OFFSET + METADATA_VERSION_FIELD_OFFSET, 
 METADATA_BASE_OFFSET + METADATA_MODULE_ID_FIELD_OFFSET, 

 SENSOR_DATA_BASE_OFFSET + 0 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_TYPE_FIELD_OFFSET,
 SENSOR_DATA_BASE_OFFSET + 0 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_UNITS_FIELD_OFFSET,
 DEBUG_BASE_OFFSET + DEBUG_NO2_HEATER_POWER_MW,
 SENSOR_DATA_BASE_OFFSET + 0 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_RAW_VALUE_FIELD_OFFSET,
 SENSOR_DATA_BASE_OFFSET + 0 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_RAW_VALUE_SENSED_RESISTANCE_OFFSET,

 SENSOR_DATA_BASE_OFFSET + 1 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_TYPE_FIELD_OFFSET,
 SENSOR_DATA_BASE_OFFSET + 1 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_UNITS_FIELD_OFFSET,
 DEBUG_BASE_OFFSET + DEBUG_CO_HEATER_POWER_MW, 
 SENSOR_DATA_BASE_OFFSET + 1 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_RAW_VALUE_FIELD_OFFSET,  
 SENSOR_DATA_BASE_OFFSET + 1 * SENSOR_DATA_ADDRESS_BLOCK_SIZE + SENSOR_RAW_VALUE_SENSED_RESISTANCE_OFFSET,  

 0xffff //terminator reserved address
};

uint8_t address_response_lengths[] = {
  4,
  6,

  16,
  16,
  4,
  8,
  4,
  
  16,
  16,
  4,
  8,
  4  

};

void setup() {
  delay(3000);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("SETUP");
  Serial.println("Address\tValue");
  Serial.println("-------------------------------");
}

void loop() {
  uint8_t ii = 0, jj = 0;
  uint8_t response_length = 4;
  while(addresses_to_read[ii] != 0xffff){
    response_length = address_response_lengths[ii];
    I2C_Get_Value(SLAVE_ADDRESS, addresses_to_read[ii], response_length);

    Serial.print(addresses_to_read[ii], HEX);
    Serial.print("\t");       
    
    if(response_length == 16){ // it must be a string
      buffer[15] = 0; // make sure it's null terminated
      Serial.print((char *) buffer); 
    }
    else if(response_length == 6){ // it's the MAC address
      for(jj = 0; jj < 6; jj++){
        if(buffer[jj] < 16) Serial.print("0");
        Serial.print(buffer[jj], HEX);
        if(jj != 5 ) Serial.print(":");
      }
    }
    else{ // it's at least one number
      Serial.print(buf_to_value(buffer), DEC);
      if(response_length == 8){   
        Serial.print(", ");
        Serial.print(buf_to_value(buffer + 4), DEC);   
      }
    }
    Serial.println();
    ii++;
    //Print_Response(buffer);  
  }
  Serial.println("-------------------------------");      
  delay(5000);
}

void I2C_Get_Value(uint8_t slave_address, uint16_t register_address, uint8_t response_length){
  I2C_Write_Address_Register(slave_address, register_address);
  delay(1); // this is definitely necessary (though shorter may be ok too)
  I2C_Read_Register_Value(slave_address, buffer, response_length);  
  delay(1); // this may not be necessary
}

void I2C_Write_Address_Register(uint8_t slave_address, uint16_t register_address){
  
  /*
    In order to read a value from the Memory Map, the Nanode 
    must write the target Sensor Module’s I2C address to bus with the Write bit set to 0 (SLA+W), 
    then write the “READ” command to the bus (0x11), 
    then write the address to be read to the bus (high byte then low byte), 
    and finally an I2C stop condition. 
  */  
  
  Wire.beginTransmission(slave_address); 
  Wire.write(CMD_READ);                        // sends READ command
  Wire.write(high_byte(register_address));     // sends register address high byte
  Wire.write(low_byte(register_address));      // sends register address low byte  
  Wire.endTransmission();                      // stop transmitting    
}

void I2C_Read_Register_Value(uint8_t slave_address, uint8_t * buf, uint8_t response_length){
  
  /* 
    The Nanode then writes the Sensor Module’s I2C address to bus with the Write bit set to 1 (SLA+R), 
    and clocks in the expected number of bytes as expected based on the address requested, 
    and finally issues an I2C stop condition.  
  */
  
  uint8_t index = 0;
  Wire.requestFrom(slave_address, response_length);   
  while(Wire.available()){    // slave may send less than requested
    buf[index++] = Wire.read();
  }  
}

void Print_Response(uint8_t * buf){
  uint8_t  index = 0;
  uint32_t value = 0;
  
  Serial.println("=HEX=");
  for(index = 0; index < MAX_RESPONSE_LENGTH; index++){
    Serial.print(buf[index], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  Serial.println("=DEC=");
  for(index = 0; index < MAX_RESPONSE_LENGTH; index++){
    Serial.print(buf[index], DEC);
    Serial.print(" ");    
  }
  Serial.println();

  Serial.println("=VALUE=");
  Serial.println(buf_to_value(buf), DEC);
  
  Serial.println("=String=");
  buf[MAX_RESPONSE_LENGTH - 1] = '\0'; //make sure its null terminated
  Serial.print((char *) buf);
  
}


/* UTILITY FUNCTIONS */

uint8_t high_byte(uint16_t value){
  return ((value >> 8) & 0xff);
}

uint8_t low_byte(uint16_t value){
  return (value & 0xff); 
}

uint32_t buf_to_value(uint8_t * buf){
  uint8_t index = 1;
  uint32_t ret = buf[0];  
  for(index = 1; index < 4; index++){
    ret = (ret << 8);         // make space for the next byte
    ret = (ret | buf[index]); // slide in the next byte
  }
  
  return ret;
}


