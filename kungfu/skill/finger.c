// finger.c

inherit SKILL;
int valid_selflearn(object me) {
	return 1;
}

int selflearn_skill(object me) { 
	if ((int)me->query("jing")<10) return 0;
	me->add("jing",-10);
	me->add("eff_jing",-10);
	return 1;
}

void skill_improved(object me)
{
    if (me->query_skill("finger",1)%30==0) {
	tell_object(me, HIW "������������գ����"+HIY"������������"+NOR+"����ˡ�"NOR"\n");
    }
}
