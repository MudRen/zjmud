// cangjingge.c �ؾ���
inherit ROOM;

string* books = ({
	"laozi1",
	"daodejing-i",
	"laozi2",
	"daodejing-i",
	"laozi8",
	"daodejing-i",
	"laozi13",
	"laozi1",
	"laozi16",
	"daodejing-i",
	"laozi18"
});

void create()
{
	set("short", "�ؾ���");
	set("long", @LONG
�����ǲؾ��󣬿�ǽ��һ����ܣ������˵��̵ĵ伮��������һ������
�εĴ����ӣ�����Ҳ�������顣һ����ͯ���������鼮���ɼ����ϵ���
ϥ������������˼���������ھ���(jingxiu)��
LONG );
	set("exits", ([
		"southdown" : __DIR__"xilang",
	]));
	set("objects", ([
		CLASS_D("wudang") + "/daotong" : 1,
		"/clone/book/"+books[random(sizeof(books))] : 1,
		"/clone/book/"+books[random(sizeof(books))] : 1
	]));
	set("item_desc", ([
		"�����ӡ�" : "���Ҿ���֮�أ��뱣�ְ�����\n"
		ZJOBACTS2"����:jingxiu1\n",
	]));
	set("no_fight", 1);
	set("sleep_room", 1);

	setup();
}

void init()
{
	add_action("do_jingxiu", "jingxiu1");
}

int do_jingxiu(string arg)
{
	object me;
	int cost;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ������ͷ��������˵��\n");

	if (me->query("jing") < me->query("max_jing") * 7 / 10)
		return notify_fail("�����ڵľ��������޷����ޡ�\n");

	if (me->query_skill("taoism", 1) < 250)
		return notify_fail("��Ե�ѧ�ķ����̫ǳ�����޻�ò���ʲô������\n");

	if (! arg || ! sscanf(arg, "%d", cost))
            return notify_fail(INPUTTXT("���������Ķ���Ǳ�������о��ޣ�","jingxiu1 $txt#")+"\n");
		//return notify_fail("��Ҫ������Ǳ�ܽ��о��ޣ�\n");

	if (cost >= me->query("potential") - me->query("learned_points"))
		return notify_fail("������û����ô���Ǳ�ܣ�\n");

	if (cost < 100)
		return notify_fail("���Ҳ̫���˰ɣ�����Ҫ��һ�ٵ�Ǳ�ܲ�������������\n");

	message_vision("$N����һ���ط�������������Ŀڤ�񣬿�ʼר���о���ѧ�ķ���\n", me);

	me->set_temp("pending/jingxiu", 1);
	me->set_temp("potential_cost", cost);
	me->set_short_desc("�����ڵ���ڤ���ޡ�");
	me->start_busy((:call_other, __FILE__, "jingxiu" :),
		       (:call_other, __FILE__, "halt_jingxiu" :));
	return 1;
}

int jingxiu(object me)
{
	int cost;

	cost = me->query_temp("potential_cost");
	if (cost > 0)
	{
		cost = random(cost) + 1;
		if (cost > 50) cost = 50;
	} else
		cost = 0;

	me->improve_skill("taoism", random(me->query_int()) + me->query_skill("taoism", 1) * cost / 3);
	me->add("learned_points", cost);
	if (me->add_temp("potential_cost", -cost) > 0)
		return 1;

	me->set_temp("pending/jingxiu", 0);
	me->set_short_desc(0);
	message_vision("$N������ϣ���¶΢Ц��վ��������\n", me);
	return 0;
}

int halt_jingxiu(object me)
{
	tell_object(me, "�������۾���վ��������\n");
	tell_room(environment(me), me->name() + "������������˫�ۣ�վ��������\n", me);
	me->set_temp("pending/jingxiu", 0);
	me->delete_temp("potential_cost");
	me->set_short_desc(0);
	return 1;
}
