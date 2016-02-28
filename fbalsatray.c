#include <gtk/gtk.h>
#include <glib.h>

void tray_icon_on_click(GtkStatusIcon *status_icon, gpointer user_data) {
	printf("YOBA\n");
}

static gboolean HandleMouseScrollWheel(GtkWidget *pWidget, GdkEventScroll *pEvent, gpointer pUserData) {
	printf("This is MOUSE WHEEL!\n");

	if(pEvent->direction == GDK_SCROLL_UP) {
		printf("\tWHEEL UP!\n");
		//SetAlsaVolume(card, selem_name, 100);
		long max,volume;
		GetAlsaVolume(&volume,&max);
		SetAlsaVolume(volume+1);
		printf("max:%ld, volume: %ld\n",max,volume);
	}
	else if(pEvent->direction == GDK_SCROLL_DOWN) {
		printf("\tWHEEL DOWN!\n");
		//SetAlsaVolume(card, selem_name, 100);
		long max,volume;
		GetAlsaVolume(&volume,&max);
		SetAlsaVolume(volume-1);
		printf("max:%ld, volume: %ld\n",max,volume);
	}

	return 0;
}

static GtkStatusIcon *create_tray_icon() {
	GtkStatusIcon *tray_icon;
	
	tray_icon = gtk_status_icon_new();
	
	g_signal_connect(G_OBJECT(tray_icon), "activate", G_CALLBACK(tray_icon_on_click), NULL);
	g_signal_connect(G_OBJECT(tray_icon), "scroll_event", G_CALLBACK(HandleMouseScrollWheel), NULL);
	gtk_status_icon_set_from_icon_name(tray_icon, GTK_STOCK_MEDIA_STOP);
    gtk_status_icon_set_tooltip(tray_icon, "Example Tray Icon");
    gtk_status_icon_set_visible(tray_icon, TRUE);
    
    return tray_icon;
}

int main(int argc, char *argv[]) {
	GtkStatusIcon *tray_icon;
	gtk_init(&argc, &argv);
	tray_icon = create_tray_icon();
	gtk_main();
	
	return 0;
}
