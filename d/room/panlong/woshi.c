// SN:HE@Ca[S1UC^3XE^7
// File(/data/room/jun/woshi.c) of jun's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set("long", "�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������
һ�����ӡ��ƿ��������Կ�������Ļ�԰�������ᵽ�����㣬�ǳ�
��⡣Զ����һ��Ƭ���֡�
");


	set("exits", ([
		"down" : __DIR__"jusuo",
	]));

	set("sleep_room", 1);
	set("loving_room", 1);
	set("no_fight", 1);
	 set("no_clean_up",1);
	setup();
    
	set("room_owner", "������");
	set("room_name", "����֮��");
	set("room_id", "home");
	set("room_owner_id", "jun");
	set("room_position", "�ݵ�");
}
int clean_up()
{
	return 0;
}