//Room: /d/foshan/southgate.c
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
�����Ƿ�ɽ������š����������ϣ��͵����Ϻ�֮���ˡ�����
һ��������Ĵ���Ƿ�ɽ�����Ҫ�ֵ���
LONG);
	set("outdoors", "foshan");
	set("exits",([ /* sizeof() == 1 */
	    "north"  : __DIR__"street3",
	    "south"  : "/d/xiakedao/xkroad3",
	]));
	setup();
}

