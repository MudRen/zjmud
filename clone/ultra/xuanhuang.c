// xuanhuang.c �������嵤

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "�������嵤" NOR, ({ "xuanhuang dan", "dan" }) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�����з��Ƶľ����浤���������񻰰�Ĺ�Ч��"
			    "�������������������ҩ��\n");
		set("value", 2500000);
		set("unit", "��");
		set("only_do_effect", 1);
	}
}

int do_effect(object me)
{
	int effect;
	int neili;

	log_file("static/using", sprintf("%s(%s) eat �������嵤 at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	effect = 0;
	message_vision(HIW "$N" HIW "һ������������һ��" +
		       this_object()->name() + HIW "��ֻ��$N"
		       HIW "����һ�������϶�ð����������"NOR"\n", me);

	me->add("combat_exp", 100000 + random(50000));
	me->improve_skill("force", 250000);
	me->improve_skill("parry", 250000);
	me->improve_skill("dodge", 250000);
	neili = me->query("max_neili") + 500;
	if (me->query("max_neili") > me->query_neili_limit())
		neili = me->query("max_neili") + 200;
	me->set("max_neili", neili);

	destruct(this_object());
	return 1;
}

