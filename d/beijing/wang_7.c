inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ���������֣�����ͨ��
�ذ��Ŷ���֡�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_9",
		"south" : __DIR__"wang_5",
		"east" : __DIR__"wang_8",
		"west" : __DIR__"dong_1",
	]));

	set("objects", ([
		__DIR__"npc/girl3" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

