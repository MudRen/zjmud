// Room: /guiyun/taihu.c
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_yell(string arg);
void reset();

void create()
{
	set("short", "̫��");
	set("long", @LONG
̫���ų������������ݣ�������������֮ˮ�Թ��ڴˡ�
��ʱ���������޲������۽Ա̣���ʮ����Դ�ͦ����������ǧ�겨
��֮�У����������Ļ��󳩡��ɴ˵Ǵ���ǰ��̫��֮�еĹ���ׯ��
LONG );
	set("outdoors", "guiyun");

	set("exits", ([
		"north"     : __DIR__"shanlu1",
	]));

	set("item_desc", ([
		"�����ߡ�" : "�����ƽ�˾�������\n"
			ZJOBACTS2"�д�:yell boat"ZJSEP"һέ�ɽ�:cross\n",
	]));
	set("objects", ([
		__DIR__"npc/xiaolu" : 1,
		__DIR__"npc/seller" : 1,
	]));

	set("resource/fish", ({ "/clone/fish/liyu",
				"/clone/fish/jiyu",
				"/clone/fish/qingyu",
				"/clone/fish/caoyu", }));

	setup();
}

void init()
{
	add_action("do_yell", "yell");
	add_action("do_cross", "cross");
}

/*�ڴ˸�Ǯ�ڶɻ������*/
/*���ȣ��ɴ����˰�������Ǯ������һ��ߺ�ȣ�������һӿ
 * ���룬СС�ɴ�Ƭ�̼��Խ���������εĺ��������ϱ���
 */

void check_trigger()
{
    object room;

    if (! query("exits/enter"))
    {
	if (! (room = find_object(__DIR__"duchuan")))
	    room = load_object(__DIR__"duchuan");
	if (room = find_object(__DIR__"duchuan"))
	{
	    if ((int)room->query("yell_trigger") == 0)
	    {
		room->set("yell_trigger", 1);
		set("exits/enter", __DIR__"duchuan");
		room->set("exits/out", __FILE__);
		message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
		    "����ϵ̰����Ա�˿����¡�\n", this_object() );
		message("vision", "������һ��̤�Ű���ϵ̰����γ�һ������"
		    "�Ľ��ݡ�\n", room);
		remove_call_out("on_board");
		call_out("on_board", 15);
	    }
	    else
		message("vision", "ֻ���ú��������������������"
		    "�����æ���š�����\n",this_object() );
	} else
	    message("vision", "ERROR: boat not found\n", this_object());
    } else 
	message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n",
		this_object());
}


void on_board()
{
    object room;

    if (! query("exits/enter")) return;

    message("vision", "������̤�Ű��������������һ�㣬���������ʻȥ��\n",
	    this_object());

    if (room = find_object(__DIR__"duchuan"))
    {
	room->delete("exits/out");
	message("vision", "������̤�Ű���������˵��һ��������ඡ���"
		"���һ�㣬���������ʻȥ��\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if (room = find_object(__DIR__"duchuan"))
    {
	room->set("exits/out", __DIR__"matou");
	message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű�"
	    "���ϵ̰���\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if (room = find_object(__DIR__"duchuan"))
    {
	room->delete("exits/out");
	message("vision", "������̤�Ű����������ѱ���ʻ����ġ�\n", room);
	room->delete("yell_trigger"); 
    }
}

int do_yell(string arg)
{
    string dir;

    if (! arg || arg == "") return 0;

    if (arg == "boat") arg = "����";
    if ((int)this_player()->query("age") < 16)
	message_vision("$Nʹ�����̵���������һ������" + arg + "��\n",
		       this_player());
    else if((int)this_player()->query("neili") > 500)
	message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ��"
		       "�˳�ȥ��\n", this_player());
    else
	message_vision("$N������������Хһ������" + arg + "����\n",
		       this_player());
    if (arg == "����")
    {
	check_trigger();
	return 1;
    } else
	message_vision("������ԶԶ����һ���������" + arg +
		       "��������\n", this_player());
    return 1;
}

int do_cross()
{
	object me;

	me = this_player();
	if (me->query_skill("dodge") < 100)
	{
		tell_object(me, random(2) ? "����ú���̫��û��ʮ��İ���Ծ��ȥ��\n"
					  : "�㿴�ź�嫵�̫�������ﲻ�����˸�ͻ��û��������\n");
		return 1;
	}

	if (me->query("neili") < 100)
	{
		tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
		return 1;
	}

	me->add("neili", -50);
	message_vision("$N����һ�Σ���ȻԾ��̫����ֻ��$P��̤�岨������Զȥ��\n", me);
	tell_object(me, "��˳���ĵ����˱˰���\n");
	me->move(__DIR__"matou");
	return 1;
}

void reset()
{
    object room;

    ::reset();
    if (room = find_object(__DIR__"duchuan"))
	room->delete("yell_trigger"); 
}
