// shufang.c �������鷿

#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "�鷿");
	set("long", @LONG
�����������ӵ����˶���д�ֵĵط����ɾ��������ķ��ı���������
�İ����������档��ʱ����Ҳ������ǩ��һЩ������˵����
LONG );

	set("default_long", "������ROOM_NAME������ROOM_OWNER����д�ֵ�"/* EXAMPLE */
			    "�ط����ɾ��������ķ��ı���������İ�����" /* EXAMPLE */
			    "�����档��ʱROOM_OWNERҲ������ǩ��(sign"/* EXAMPLE */
			    ")һЩ������˵����");		  /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"east" : __DIR__"jusuo",
	]));

	set("sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_sign", "sign");
}

int do_sign()
{
	object ob;
	object me;

	me = this_player();

//**	if (! is_room_owner(me))
//**		return notify_fail("���ֲ�����������ˣ��Ҹ�"
//**				   "ʲô��\n");

	if (me->is_busy())
		return notify_fail("�����ڻ�æ���ء�\n");
	 
	message_vision("$N���һ��ֽ����������������滭����"
		       "��д��Щ������\n", me);
	tell_object(me, "��д��һ�����͡�\n");

	ob = new("/d/room/roomobj/pass");
	ob->set_name(HIW + me->query("name") + "����" NOR,
		     ({ "pass", query("room_owner_id") + " pass" }));
	ob->set("long", "һ����" + me->query("name") + "�ױ�ǩ����" +
		     "���ͣ�ƾ��������Խ���" + query("room_name") +
		     "��\n");
	ob->move(me);
	return 1;
}
