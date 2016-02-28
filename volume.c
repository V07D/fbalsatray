#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#include <stdio.h>

void SetAlsaVolume(const char* card, const char* selem_name, long volume);
void GetAlsaVolume(const char* card, const char* selem_name, long* volume, long max);
void SetAlsaSwitchMute(const char* card, const char* selem_name);

void SetAlsaSwitchMute(const char* card, const char* selem_name) {
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);
    
    int* muted;
    snd_mixer_selem_channel_id_t channel;
    
    snd_mixer_selem_get_playback_switch(elem,channel,muted);
    printf("Muted: %d\n",*muted);	

    if (snd_mixer_selem_has_playback_switch(elem)) {
        snd_mixer_selem_set_playback_switch_all(elem, !*muted);
    }

    snd_mixer_close(handle);
}

snd_mixer_elem_t* GetElem(const char* card, const char* selem_name) {
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    return elem;
}

void SetAlsaVolume(const char* card, const char* selem_name, long volume) {
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    // snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);
    snd_mixer_selem_set_playback_volume_all(elem, volume);

    snd_mixer_close(handle);
}

void GetAlsaVolume(const char* card, const char* selem_name, long* volume, long max) {
    long min;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    // snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_selem_get_playback_volume(elem,0,volume);

    snd_mixer_close(handle);
}

// int main() {
// 	const char *card = "default";
// 	const char *selem_name = "Master";
	
// 	//~ SetAlsaSwitchMute(card, selem_name);
// 	SetAlsaVolume(card, selem_name, 30);
		
// 	return 0;
// }
