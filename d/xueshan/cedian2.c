//      cedian2.c ���
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
������ѩɽ�µ�����ǽ��������ŷ��洫���Ĺ�
�£���������𻨱���ׯ�ϡ�
LONG );
	set("exits", ([
		"north" : __DIR__"zoulang2",
		"east" : __DIR__"dadian",
	]));
	set("objects", ([
		CLASS_D("xueshan")+"/samu" : 1,
		__DIR__"npc/xiang-ke" : 3,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	myfam=(mapping)me->query("family");
	if( (!myfam || myfam["family_name"] !="ѩɽ��") && dir=="north"
	&& objectp(present ("samu huofo" ,environment(me) ))) 
		return notify_fail("��ľ���˵�� : ���ѩɽ�µ��� ,��������!! \n");
	return ::valid_leave(me,dir);
}
