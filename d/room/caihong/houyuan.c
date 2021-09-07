// houyuan.c �ʺ�Ӻ�Ժ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "��Ժ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME��Ժ");
	set("long", @LONG
���ǲʺ�ӵĺ�Ժ������һЩ���ݣ��󲿷��Ƕ���֪����Ұ�����ݡ�
��������������Ҳ����ȥҲ�ǳ�Ư�������������������ƣ���ˣ��Ϳ�
�Ե�����������Ϣ��Ժ�Ƿ���һ�����Ρ�
LONG );

	set("default_long", "����ROOM_NAME�ĺ�Ժ������һЩ���ݣ���"  /* EXAMPLE */
			    "�����Ƕ���֪����Ұ�����ݡ�������������" /* EXAMPLE */
			    "��Ҳ����ȥҲ�ǳ�Ư������ʱROOM_OWNER��" /* EXAMPLE */
			    "������ƣ���ˣ��͵���������Ƭ������Ϣ��" /* EXAMPLE */
			    "Ҳ��ʱ���������������������д�һ��" /* EXAMPLE */
			    "���ա�");			       /* EXAMPLE */
								     /* EXAMPLE */
	setup();

	set("exits", ([
		"south"  : __DIR__"dating",
	]));

	set("outdoors", "OUTDOORS");
	set("sleep_room", 1);

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
	add_action("do_sit", "sit");
	this_player()->delete_temp("has_sit");
}

int do_sit(string arg)
{
	object me;

	me = this_player();
	if (me->query_temp("has_sit"))
	{
		message_vision("$N��������ҡ��ҡ���ò���⡣\n", me);
		return 1;
	}

	message_vision("$N���˵ĵط���������������ȥ���ɶ��ˡ�\n", me);
	me->set_temp("has_sit", 1);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("has_sit"))
	{
		message_vision("$N����������վ��������\n", me);
		me->delete_temp("has_sit");
	}

	return ::valid_leave(me, dir);
}
