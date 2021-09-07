//room: jian.c

inherit ROOM;

void init();
int do_zou(string);

void create()
{
	set("short","���ɽ�");
	set("long",@LONG
ɽ������ͻȻ��ʧ��������ǰ��һ��ɽ����ɽ��֮���������ƣ����
���޷�������档һ������(tiesuo)�������У��Ա���һ��ʯ��(bei)��
LONG );
	set("outdoors", "lingjiu");
	set("exits",([
		"southdown" : __DIR__"yan",
		"east" : __DIR__"jingji/enter",
	]));
	set("objects",([
		__DIR__"npc/yupopo" : 1,
	]));
	set("item_desc",([
		"��ʯ����" : HIR"�����չ����صأ�����������"NOR"\n" ,
		"��������" : "����ͨ������ġ������š�����Ҳ������߹�(zou)ȥ��\n"
			ZJOBACTS2"ͨ��:zou tiesuo\n",
	]));
	setup();
}

void init()
{
	add_action("do_zou", "zou");
}

int do_zou(string arg)
{
	object me=this_player(), room;

	if(!arg || arg!="tiesuo")
		return notify_fail("��Ҫ��ʲô��\n");

	if(!( room = find_object(__DIR__"xianchou")) )
		room = load_object(__DIR__"xianchou");

	if(!objectp(room))
		return notify_fail("ERROR:not found 'xianchou.c' \n");
	message_vision("$N����������ƮȻ��ȥ��\n", me);
	me->move(room);
	return 1;
}

