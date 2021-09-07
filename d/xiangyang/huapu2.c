// Room: /d/xiangyang/huapu2.c  ����
// Date: Jan. 28 2002 by Pound

inherit ROOM;

int do_jiao(string);

void create()
{
	set("short", "����");
	set("long", @LONG
˳�Ż��Լ��С·�����߼�����ֻ���ڶ��Ͻ��и���أ�fenchi����
����Ʈ��Щ����ζ�����������ķ����ˮϡ�͹�����������ֱ������
����ʩ�ʡ�
LONG
	);
	set("exits", ([
	    "north" : __DIR__"huapu",
	]));
	set("item_desc", ([
	    "fenchi" : "������и����ף���������װ�ཽ(jiao)����\n",
	]));

	set("outdoors", "xiangyang");
	setup();
}

void init()
{
	add_action("do_jiao", "jiao");
}

int do_jiao(string arg)
{
	object me;
	me = this_player();

	if (me->is_busy() )
	{
	    return notify_fail("��������æ���ء�\n");
	}

// ��΢����һ������Ѷȣ���ò������������Ӧ�����Ͷ����赹�ļ����Դ�
	if (me->query_temp("yaowang/jiao") > 26 && me->query("per") > random(50))
	{
	    message_vision("$N�ڷ����Ҩ�˼��£�ͻȻһ��Ũ�ĳ����������������Ѭ��$N���˹�ȥ��\n", me);
	    me->set_temp("yaowang/jiao", 0);
	    me->unconcious();
	    return 1; 
	}

//      set_temp("die_reason", "Ҩ�ཽ�����͹��ȣ��۵��ڷ��������");
	me->receive_damage("qi", 30);
	me->add_temp("yaowang/jiao", 1);
	message_vision("$N�ӷ����Ҩ��һ�׷�齽���˻��ϣ�һ�����Ѭ��$N������Ż��\n", me);
	me->start_busy(2); 

	if (me->query("qi") < 100)
	    tell_object(me, "���Ѿ��۵��������ۣ�ֱ�������ˡ�\n");
	return 1;
}

