// cuff.c

inherit SKILL;
void skill_improved(object me)
{
    if (me->query_skill("cuff",1)%30==0) {
	tell_object(me, HIW "������������գ����"+HIY"������������"+NOR+"����ˡ�"NOR"\n");
    }
}
