// xiaoyuan.c

inherit ROOM;

#define GANJIANG	"/adm/npc/ganjiang"
#define MOYE	    "/adm/npc/moye"

void create()
{
	object ob;

	set("short", "������");
	set("long", @LONG
��һ�߽�������ӣ��͸о�����һ����������������ݽ���һ��¯�ӣ�
����ȼ�����ܻ�⣬�ƺ������Ľ���������ǰ�ζ����ݽǶѷ���һ�ѶѺ�
�����Ķ�������֪����ʲô��
LONG );

	GANJIANG->come_here();
	MOYE->come_here();

	set("no_fight", 1);
	set("no_sleep_room", 1);

	set("exits", ([
		"west" : __DIR__"road5",
	]));
	set("action_list", ([
		HIC"��������"NOR:"name",
		HIG"�趨����"NOR:"desc",
		HIY"װ������"NOR:"wieldmsg",
		HIY"��������"NOR:"removemsg",
		HIM"�����趨"NOR:"finish",
	]));
	setup();
}
