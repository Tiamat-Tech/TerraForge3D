#include "MeshNodeEditor.h"
#include "imgui.h"
#include "Base/ImGuiShapes.h"
#include "Base/NodeEditor/NodeEditor.h"
#include "Utils.h"

// Nodes
#include "Nodes/DummyNode.h"

static int* resolution;
static NodeEditor* editor;

MeshNodeEditorResult EvaluateMeshNodeEditor(MeshNodeEditorParam param)
{
    return MeshNodeEditorResult();
}

nlohmann::json GetMeshNodeEditorSaveData()
{
    return nlohmann::json();
}

void SetMeshNodeEditorSaveData(nlohmann::json data)
{
}

void SetupMeshNodeEditor(int* res)
{
    resolution = res;
    editor = new NodeEditor(NodeEditorConfig(GetExecutableDir() + "\\Data\\configs\\meshnodeeditorconfigs.terr3d"));
}

void MeshNodeEditorTick()
{
}

void ShutdownMeshNodeEditor()
{
    if (editor)
        delete editor;
}

void ShowMeshNodeEditor(bool* pOpen)
{
    ImGui::Begin("Mesh Node Editor", pOpen);
    if (ImGui::Button("Add Node")) 
    {
        editor->AddNode(new DummyNode());
    }

    ImGui::Text("WARNING : Work In Progress!");
    
    editor->Render();

    ImGui::End();
}
