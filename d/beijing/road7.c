
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ�
���̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·������
��������������֡�
LONG );
	set("exits", ([
		"northwest" : __DIR__"road6",
		"east" : __DIR__"road4",
	]));
	set("objects", ([
		"/d/huashan/npc/haoke" : 1,
	]));
 	set("outdoors", "beijing");
	setup();
}
