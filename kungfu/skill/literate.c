// literate.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
	return 1;
}


void skill_improved(object me)
{
    int s;
    s = me->query_skill("literate", 1);

    if (s%10==0){
	tell_object(me, HIW "��������ѧ��������"+HIY"���������ԡ�"+NOR+"����ˡ�\n");
    }

}
