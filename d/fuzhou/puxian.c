// Room: /d/fuzhou/puxian.c
inherit ROOM;

void create()
{
	set("short", "����ƽԭ");
	set("long", @LONG
����������ƽԭ�ϡ�����������ģ����̳��ܣ�������
�Ǹ��ݸ����ˡ����Ͼͽ������ϡ�
LONG );
	set("exits", ([
		"north" : __DIR__"zhongzhou",
		"south" : "/d/quanzhou/beimen",
	]));
	set("outdoors", "fuzhou");
	setup();
}

