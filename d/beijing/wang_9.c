inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ���������֣������Ƿ�
���ĵذ��Ŷ���ֹ㳡�����������ض���ֿ��Ե�������
LONG );
       set("exits", ([
		"north" : __DIR__"dong_3",
		"south" : __DIR__"wang_7",
		"east" : __DIR__"wang_10",
		"west" : __DIR__"di_donggc",
	]));

	set("objects", ([
		__DIR__"npc/haoke1" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

