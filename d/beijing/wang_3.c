inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ��Ǿ��ǵĽ�ͨҪ���������֡�������һ
��������У���������ﴫ��һ����ʿ�������������������ǳ�������ͨ�����ţ�
���˳����ž��Ǳ����ǵ������ˡ�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_5",
		"south" : __DIR__"wang_1",
		"east" : __DIR__"wang_4",
		"west" : __DIR__"xiaochang",
	]));
	set("objects", ([
		__DIR__"npc/bing1" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

