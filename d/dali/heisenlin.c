//Room: /d/dali/heisenlin.c
inherit ROOM;
void create()
{
	set("short","��ɭ��");
	set("long",@LONG
ӭ��һ��Ƭ��ѹѹ��ɭ�֣��ߴ�Ĺ��ɲ������������һ��
�������������������Щ�ر�
LONG);
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "south"      : __DIR__"dasenlin",
	]));
	set("no_clean_up", 0);
	setup();
}

