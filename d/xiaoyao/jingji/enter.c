#include <room.h>
#include <huodong.h>
inherit ROOM;
#define FAMILY "��ң��"
#define OUTROOM "/d/xiaoyao/xiaodao4"
#include <jjenter.h>

void create()
{
	set("short", "������");
	set("long", "������"+FAMILY+"���ɾ���������ڡ�");
	set("exits", ([
		"south" : OUTROOM,
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
