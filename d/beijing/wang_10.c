inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ���������֣����߲�Զ
���Ƿ����ĵذ��Ŷ���ֹ㳡�������Ǿ��������ġ�ȫ�۵¡���Ѽ�ꡣ������
һ��ϷԺ���Ǿ��ǰ�����Ϣ�����ֵĳ�����
LONG );
       set("exits", ([
		"north" : __DIR__"quanjude",
		"south" : __DIR__"wang_8",
		"west" : __DIR__"wang_9",
		"east" : __DIR__"xiyuan",
	]));

	set("objects", ([
		__DIR__"npc/youren" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

