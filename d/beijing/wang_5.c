inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ��Ǿ��ǵĽ�ͨҪ���������֡��򱱿���
�ذ��Ŷ���֡�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_7",
		"south" : __DIR__"wang_3",
		"east" : __DIR__"wang_6",
	]));

	setup();
       set("outdoors", "beijing");
}

