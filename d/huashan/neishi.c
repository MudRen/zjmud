// Room: /d/huashan/neishi.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������Щ�谵����������������ҳ�������ƽʱ��û�������ڴ�ɨ��
��һЩ���ڵ���бб�Ŀ��ڽ���Ĵ��ϳ�����˯�š�
LONG );
	set("exits", ([ /* sizeof() == 4 */
	     "west": __DIR__"xiaowu",
	]));
	set("no_fight", 1);
	set("sleep_room", 1);

	setup();
}
