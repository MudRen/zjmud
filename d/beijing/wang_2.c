inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ��Ǿ��ǵĽ�ͨҪ���������֡���������
������һ�������ûʵĽ��������ǵ������ϵĵ�һ�購����Τ��ү�ĸ�ۡ����
�߾��Ǿ��ǵ��̳����ǳ�͢�����շ��ĳ�����
LONG );
       set("exits", ([
		"north" : __DIR__"wang_4",
		"south" : __DIR__"caroad_e2",
		"east" : __DIR__"xingchang",
		"west" : __DIR__"wang_1",
	]));
	set("objects", ([
		__DIR__"npc/shusheng1" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

