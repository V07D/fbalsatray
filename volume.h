void SetAlsaVolume(long volume);
void GetAlsaVolume(long* volume);
void SetAlsaSwitchMute(const char* card, const char* selem_name);
struct alsa_control_struct GetStruct(const char* card, const char* selem_name);