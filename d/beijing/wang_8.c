inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ���������֣�����ͨ��
�ذ��Ŷ���֡��Ӷ��ߴ���һ�����ӵ������������Ǿ�������������Ժ��
LONG );
       set("exits", ([
		"north" : __DIR__"wang_10",
		"south" : __DIR__"wang_6",
		"east" : __DIR__"yihongyuan",
		"west" : __DIR__"wang_7",
	]));

	set("objects", ([
		__DIR__"npc/richman1" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

