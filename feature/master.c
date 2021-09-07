// master.c

#include <dbase.h>

int can_learn_from() { return 1; }

int prevent_learn(object me, string skill)
{
	mapping fam;

	if (! me->is_apprentice_of(this_object()) &&
	    mapp(fam = me->query("family")) &&
	    fam["family_name"] == query("family/family_name"))
	{
		command("say ��Ȼ���������µĵ��ӣ����ǲ����ҵĵմ���"
			"��... ����ȥ����ʦ��ѧ�ɡ�");
		return 1;
	}

	return 0;
}

void attempt_detach(object me)
{
	if (! me->is_apprentice_of(this_object()))
	{
		command("say ��ȥ������ʦ����");
		return;
	}

	command("sigh");
	command("say �߰��߰ɣ����߰ɣ�����ѧ�����书���£�");

	me->skill_expell_penalty();
	me->unconcious();

	message_vision("$N������ճ��$n�ı��������"
		       "��֪����˵Щʲô��\n", this_object(), me);
	me->add("detach/" + me->query("family/family_name"), 1);
	me->delete("family");
	me->set("title", "��ͨ����");
}

