
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ�
���̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·������
��������������֡��������������������Ͼ��ǡ��ϱ�ͨ������
�ǡ�
LONG );
	set("exits", ([
		"north" : __DIR__"road3",
		"west" : __DIR__"road7",
		"south" : __DIR__"road8",
	]));
	set("objects",([
		"/d/taishan/npc/jian-ke" : 1,
	]));
 	set("outdoors", "beijing");
	setup();
}

