// yuchanda.c

inherit ITEM;

void create()
{
	set_name("ѩ����󸵤", ({"yuchan dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "\n���Ǹ�����������ҩ������ⶾ���ˣ�����Ƿ���\n");
		set("value", 10000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->improve_neili(1);
	message_vision("$N����һ��ѩ����󸵤��ֻ��һ�ɺƵ�����ֱӿ"
		       "��������æ��ϥ��������Ŀ�˹�...\n" , me);
	destruct(this_object());
	return 1;
}
