// flyon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_flyon(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj, *env,obn;

	if (! arg) return notify_fail("��Ҫ����ʲô������\n");

	if (me->query_skill("fly", 1) < 100 ) 
		return notify_fail("���������̫�����ˤ������(100�����Ϸ�����������)\n");    

	if (me->query_temp("is_flying"))
		return notify_fail("���Ѿ�������������״̬�ˣ�\n");

	if (me->is_busy())
		return notify_fail("����һ��������û����ɣ�\n");

	if (me->is_fighting())
		return notify_fail("�㻹��ս���У�û�ռ����ɽ�ȥ��\n");

	// Check if a container is specified.
	 if (! objectp(obj = present(arg,me)))
	return notify_fail("��û�ж������Լ������С�\n");
	 
	 if (obj->item_owner() && obj->apply_damage() && (int)obj->weapon_level()>=9)
	  {
	       return do_flyon(me, obj);
	  }
	 else
	  {
		return notify_fail("���޷�����< "+obj->query("name")+" >���С�(9�����ϱ������ܼ���)\n");
	  }
	return write("վ���˷ɽ��ϡ�\n");
       
	
}
	
int do_flyon(object me, object obj)
{
	object old_env;

	if( !obj ) return 0;

	//obj->set_weight(1);
	
		message_vision( "$N����Ծ��$n�����������"+obj->query("name")+"�Զ�������\n", me, obj );
		obj->set_temp("is_flyed_by", me);
		me->set_temp("is_flying", obj);
	
	
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : flyon <�ɽ�ID>
 
���ָ�������������Լ��ķɽ��������������˲Ϣ���
 
HELP
    );
    return 1;
}
