inherit ROOM;

void create()
{
	set("short", "�͵��Ժ");
	set("long", @LONG
����͵��Ժ��һ�����֮���Ӷ�����᷿ (room) �д��������м���
��һ��Ů�ӵ����������ŵİ��(wall)��ס���𶯣��ƺ��ͷ����ܵİ�ڶ�Ҫ
������������̮һ�㡣�����ǿ͵���š�
LONG );
	set("no_sleep_room",1);
	set("exits", ([
		"east" : __DIR__"kefang",
		"south" : __DIR__"fukedian",
	]));
	set("item_desc", ([
		"wall" : "\n����һ��ľǽ����ڲ���һ�����񣬱����ҡҡ�λΡ�\n",
		"room" :
"\n����������ȥ��ֻ�����������ֳֽ䵶��Χ��һ����Ů��ƴ����ɱ��\n"+
"ֻ�Ǹ�����Ů��������Ʒ��ס�ˣ��۲��������ǰ���Ů��ͷ����ð\n"+
"��˿˿��������Ȼ�Ѿ���ȫ������ֻһ���۰���֧����ȥ�������ԵֵС�\n"+
"���ϰ߰ߵ�㶼��Ѫ����\n",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	int i;
	object room;

	if (dir != "east" )
		return ::valid_leave(me, dir);

	room = find_object(query("exits/east"));
	if (! room) room = load_object(query("exits/east"));
	if (room && present("la ma", room) && present("dubi shenni", room))
	{
		if ((int)me->query_skill("force") < 100) 
			return notify_fail("\n��һ��̤���ͷ���ͻ��һ��������"
					   "��ľ��缤�˳���������һײ��\n"
					   "���ʱ���㲻�ȣ������ڵ���������"
					   "һ��������\n");
		me -> receive_damage ("qi",50) ;
		me -> receive_wound  ("qi",50) ;
	}
	return ::valid_leave(me, dir);
}

void init()
{
	add_action("do_thrust","thrust");
	add_action("do_thrust","ci");
	add_action("do_thrust","stab");
}

int do_thrust(string arg)
{
	object room, me,man;
	object weapon;

	if (! arg || arg != "wall" ) return notify_fail("��Ҫ��ʲô��\n");

	weapon = this_player()->query_temp("weapon");
	if (! weapon ||
	    (weapon->query("skill_type") != "sword" &&
	     weapon->query("skill_type") != "blade"))
		return notify_fail("���õ������²��аɣ�\n");

	if (!( room = find_object(__DIR__"kefang")))
		room = load_object(__DIR__"kefang");

	if (man = present("la ma", room))
	{
		message_vision("\n$N�ߵ�ǽ�ߣ�������У���׼ľ���"
			       "�ݵ�һ����\n",this_player());

		if (this_player()->query_temp("apply/damage") < 100)
		{
			message_vision("���$N�Ƶ�һ�������в��������Ҳ"
				       "�̲�����֡�\n",this_player());
			return 1;
		}

		message_vision("ֻ���۵�һ����ذ�����ᴩ��ľ�壬������ʱ��"
			       "��һ���ҽС�\n",this_player());
		message("vision", "��Ȼһ������ҽ�һ��������ȥ��\n",room );
		man->die();	     
	}
	else return notify_fail("����û�����������ɱ�ˡ�\n");

	return 1;
}

