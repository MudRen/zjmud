// Room: /d/xuedao/xiuxishi

inherit ROOM;

void create()
{
	set("short", "�ප");
	set("long", @LONG
������һ��СС��ɽ�����������˺ܶ�é�ݣ��ǳ��������
��Щ�谵��ֻ������͸��һЩ���⡣�㲻��������Щ���ˣ�һʱ��
��ס������˯˯��
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"shandong3",
	]));
	setup();
}
