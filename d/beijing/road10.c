
inherit ROOM;

void create()
{
	set("short", "С��");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ�
���̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·������
��������������֡����߾��Ǵ�֮���ˡ�
LONG );
	set("exits", ([
		"east"  : __DIR__"haigang",
		"south" : "/d/shaolin/ruzhou",
		"north" : __DIR__"road9",
	]));
	set("objects",([
		"/d/taishan/npc/tiao-fu" : 1,
	]));
 	set("outdoors", "beijing");
	setup();
}



