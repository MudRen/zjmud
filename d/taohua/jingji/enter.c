#include <room.h>
#include <huodong.h>
inherit ROOM;
#define FAMILY "�һ���"
#define OUTROOM "/d/taohua/tingzi"
#include <jjenter.h>

void create()
{
	set("short", "������");
	set("long", "������"+FAMILY+"���ɾ���������ڡ�");
	set("exits", ([
		"west" : OUTROOM,
	]));
	set("no_fight",1);
	set("no_fly",1);
	set("objects",([
	]));
	set("action_list",([
		"�����":"jjsign",
	]));
	setup();
}
