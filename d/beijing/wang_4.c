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
		"north" : __DIR__"wang_6",
		"south" : __DIR__"wang_2",
		"east" : __DIR__"chaoyang_dao1",
		"west" : __DIR__"wang_3",
	]));

	setup();
       set("outdoors", "beijing");
}

